#!/usr/bin/env python3

import sys
import os

class Member:
    def __init__(self, mtype, mname):
        self.mname = mname
        self.is_ptr = mtype.endswith("*")
        self.mtype = mtype[:-1] if self.is_ptr else mtype

class Klass:
    def __init__(self, name, members):
        self.name = name
        self.members = members

class Include:
    def __init__(self, file):
        self.is_std = file.endswith("*")
        self.file = file[:-1] if self.is_std else file

def split_description(description):
    return map(str.strip, description.split("="))

def split_member_description(description):
    return map(str.strip, description.split(" "))

def get_members(member_desc):
    return [Member(*split_member_description(description)) for description in member_desc.split(", ")]

def get_includes(line):
    files_str = line.split("=")[1].strip()
    return map(Include, files_str.split(", "))

def get_klass(line):
    name, member_descriptions = split_description(line)
    members = get_members(member_descriptions)
    return Klass(name, members)

def read_file(desc_file):
    with open(desc_file) as infile:
        lines = infile.readlines()
    includes = []
    klasses = []
    for line in lines:
        if line.startswith("%includes"):
            includes.extend(get_includes(line))
        else:
            klasses.append(get_klass(line))
    return includes, klasses

class Writer:
    def __init__(self, file):
        self.file = file

    def writeln(self, line=""):
        self.file.write(line + "\n")

    def emmit_blank(self):
        self.file.write("\n")

def tabs(n):
    return "\t" * n

def generate_fwd_declarations_file(klasses, base, writer):
    writer.writeln("/*******************************")
    writer.writeln("*" + tabs(1) + "File generated by ast_generator.py, DO NOT MODIFY!")
    writer.writeln("*******************************/")
    writer.emmit_blank()
    writer.writeln("#ifndef " + base.upper() + "_FWD_HPP")
    writer.writeln("#define " + base.upper() + "_FWD_HPP")
    writer.emmit_blank()
    for klass in klasses:
        writer.writeln(f"struct {klass.name};")
    writer.emmit_blank()
    writer.writeln("#endif")

def get_parameter_type(member):
    return f"std::shared_ptr<{member.mtype}>" if member.is_ptr else member.mtype

def generate_class_decl(klass, base, writer):
    parameters = ", ".join(map(get_parameter_type, klass.members))
    writer.writeln(f"struct {klass.name}: public {base} {{")
    for member in klass.members:
        writer.writeln(f"{tabs(1)}{get_parameter_type(member)} {member.mname};")
    writer.writeln(f"{tabs(1)}{klass.name}({parameters});")
    writer.writeln(f"{tabs(1)}void accept(Mutable_state_visitor&);")
    writer.writeln("};")
    writer.emmit_blank()

def generate_header_file(includes, klasses, base, writer):
    writer.writeln("/*******************************")
    writer.writeln("*" + tabs(1) + "File generated by ast_generator.py, DO NOT MODIFY!")
    writer.writeln("*******************************/")
    writer.emmit_blank()
    writer.writeln("#ifndef " + base.upper() + "_HPP")
    writer.writeln("#define " + base.upper() + "_HPP")
    writer.emmit_blank()
    for include in includes:
        if include.is_std:
            writer.writeln(f"#include <{include.file}>")
    writer.emmit_blank()
    for include in includes:
        if not include.is_std:
            writer.writeln(f"#include \"{include.file}\"")
    writer.emmit_blank()
    writer.writeln(f"struct {base} {{")
    writer.writeln(f"{tabs(1)}virtual void accept(Mutable_state_visitor&) = 0;")
    writer.writeln(f"{tabs(1)}virtual ~{base}() {{}};")
    writer.writeln("};")
    writer.emmit_blank()
    for klass in klasses:
        generate_class_decl(klass, base, writer)
    writer.emmit_blank()
    writer.writeln("#endif")

def get_parameter(member):
    return f"{get_parameter_type(member)} p_{member.mname}"

def generate_class_impl(klass, base, writer):
    parameters = ", ".join(map(get_parameter, klass.members))
    writer.writeln(f"{klass.name}::{klass.name}({parameters}):")
    initializer = ", ".join(map(lambda member: f"{member.mname} {{p_{member.mname}}}", klass.members))
    writer.writeln(f"{tabs(1)}{initializer} {{}}")
    writer.emmit_blank()
    writer.writeln(f"void {klass.name}::accept(Mutable_state_visitor& visitor) {{")
    writer.writeln(f"{tabs(1)}visitor.visit(*this);")
    writer.writeln("}")
    writer.emmit_blank()

def generate_impl_file(includes, klasses, base, writer):
    writer.writeln("/*******************************")
    writer.writeln("*" + tabs(1) + "File generated by ast_generator.py, DO NOT MODIFY!")
    writer.writeln("*******************************/")
    writer.emmit_blank()
    for include in includes:
        if include.is_std:
            writer.writeln(f"#include <{include.file}>")
    writer.emmit_blank()
    for include in includes:
        if not include.is_std:
            writer.writeln(f"#include \"{include.file}\"")
    writer.emmit_blank()
    writer.writeln(f"#include \"Ast/{base.lower()}.hpp\"")
    writer.emmit_blank()
    for klass in klasses:
        generate_class_impl(klass, base, writer)

def main():
    if len(sys.argv) != 3:
        print("Usage:", sys.argv[0], "<base>", "<desc_file>")
        exit(64)

    _, base, desc_file = sys.argv
    output_dir = "src/Ast/"

    includes, klasses = read_file(desc_file)

    fwd_filename = os.path.join(output_dir, base.lower() + "_fwd.hpp")
    with open(fwd_filename, "w") as file:
        writer = Writer(file)
        generate_fwd_declarations_file(klasses, base, writer)

    header_filename = os.path.join(output_dir, base.lower() + ".hpp")
    with open(header_filename, "w") as file:
        writer = Writer(file)
        generate_header_file(includes, klasses, base, writer)

    impl_filename = os.path.join(output_dir, base.lower() + ".cpp")
    with open(impl_filename, "w") as file:
        writer = Writer(file)
        generate_impl_file(includes, klasses, base, writer)

if __name__ == "__main__":
    main()


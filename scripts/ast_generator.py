#!/usr/bin/env python3

import sys

class Member:
    def __init__(self, mtype, mname):
        self.mtype = mtype
        self.mname = mname

class Klass:
    def __init__(self, name, members):
        self.name = name
        self.members = members

def split_description(description):
    splitted = description.split(":")
    return (item.strip() for item in splitted)

def split_member_description(description):
    splitted = description.split(" ")
    return (item.strip() for item in splitted)


def get_members(member_desc):
    members = []
    descriptions = member_desc.split(", ")
    for description in descriptions:
        mtype, mname = split_member_description(description)
        members.append(Member(mtype, mname))
    return members

def read_classes(desc_file):
    klasses = []
    with open(desc_file) as infile:
        descriptions = infile.readlines()
        for description in descriptions:
            name, member_descriptions = split_description(description)
            members = get_members(member_descriptions)
            klasses.append(Klass(name, members))
    return klasses

class Writer:
    def __init__(self, filename):
        self.file = open(filename, "w")

    def writeln(self, line = ""):
        self.file.write(line + "\n")

    def emmit_blank(self):
        self.file.write("\n")

    def close(self):
        self.file.close()
        self.file = None

def tabs(n):
    return "\t" * n

def generate_fwd_declarations_file(klasses, base, writer):
    writer.writeln("#ifndef " + base.upper() + "_FWD_H")
    writer.writeln("#define " + base.upper() + "_FWD_H")
    writer.emmit_blank()
    for klass in klasses:
        writer.writeln("struct " + klass.name + ";")
    writer.emmit_blank()
    writer.writeln("#endif")

def generate_class_decl(klass, base, writer):
    parameters = ", ".join(
        map(lambda member: "std::shared_ptr<" + member.mtype + ">", klass.members))
    writer.writeln("struct " + klass.name + ": public " + base + " {")
    for member in klass.members:
        writer.writeln(tabs(1) + "std::shared_ptr<" + member.mtype +
                "> " + member.mname + ";")
    writer.writeln(tabs(1) + klass.name +
            "(" + parameters + ");")
    writer.writeln(tabs(1) + "void accept(Mutable_state_visitor&);")
    writer.writeln("};")

def generate_header_file(klasses, base, writer):
    writer.writeln("#ifndef " + base.upper() + "_H")
    writer.writeln("#define " + base.upper() + "_H")
    writer.emmit_blank()
    writer.writeln("#include <memory>")
    writer.emmit_blank()
    writer.writeln("#include \"../Token/token.h\"")
    writer.writeln("#include \"../Variant/literal.h\"")
    writer.writeln("#include \"../Visitor/mutable_state_visitor.h\"")
    writer.emmit_blank()
    for klass in klasses:
        writer.writeln("struct " + klass.name + ";")
    writer.emmit_blank()
    writer.writeln("struct " + base + " {")
    writer.writeln(tabs(1) + "virtual void accept(Mutable_state_visitor&) = 0;")
    writer.writeln("};")
    writer.emmit_blank()
    for klass in klasses:
        generate_class_decl(klass, base, writer)
    writer.emmit_blank()
    writer.writeln("#endif")

def generate_class_impl(klass, base, writer):
    parameters = ", ".join(
        map(lambda member: "std::shared_ptr<" + member.mtype + "> "
            + "p_" + member.mname, klass.members))
    writer.writeln(klass.name + "::" + klass.name + "(" + parameters + "):")
    initializer = ", ".join(
        map(lambda member: member.mname + " {p_" + member.mname + "}", klass.members))
    writer.writeln(tabs(1) + initializer + " {}")
    writer.emmit_blank()
    writer.writeln("void " + klass.name + "::accept(Mutable_state_visitor& visitor) {")
    writer.writeln(tabs(1) + "visitor.visit(*this);")
    writer.writeln("}")
    writer.emmit_blank()

def generate_impl_file(klasses, base, writer):
    writer.writeln("#include <memory>")
    writer.emmit_blank()
    writer.writeln("#include \"../Token/token.h\"")
    writer.writeln("#include \"../Variant/literal.h\"")
    writer.writeln("#include \"../Visitor/mutable_state_visitor.h\"")
    writer.writeln("#include \"" + base.lower() + ".h\"")
    writer.emmit_blank()
    for klass in klasses:
        generate_class_impl(klass, base, writer)

def main():
    if len(sys.argv) != 4:
        print("Usage:", sys.argv[0], "<base>", "<desc_file>", "<output_dir>")
        exit(64)
    
    _, base, desc_file, output_dir = sys.argv

    klasses = read_classes(desc_file)
    
    fwd_filename = output_dir + "/" + base.lower() + "_fwd.h"
    writer = Writer(fwd_filename)
    generate_fwd_declarations_file(klasses, base, writer)
    writer.close()
    
    header_filename = output_dir + "/" + base.lower() + ".h"
    writer = Writer(header_filename)
    generate_header_file(klasses, base, writer)
    writer.close()
    
    impl_filename = output_dir + "/" + base.lower() + ".cpp"
    writer = Writer(impl_filename)
    generate_impl_file(klasses, base, writer)
    writer.close()

main()

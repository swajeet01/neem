#!/usr/bin/env python3

import sys

if len(sys.argv) != 3:
    print("Usage:", sys.argv[0], "<desc_file>", "<output_dir>")
    exit(64)

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

def get_classes(desc_file):
    klasses = []
    with open(sys.argv[1]) as desc_file:
        descriptions = desc_file.readlines()
        for description in descriptions:
            name, member_descriptions = split_description(description)
            members = get_members(member_descriptions)
            klasses.append(Klass(name, members))
    return klasses

def generate_fwd_declarations_file(klasses):
    pass 

def generate_header_file(klasses):
    pass

def generate_impl_file(klasses):
    pass


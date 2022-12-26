#!/usr/bin/env python

from __future__ import print_function
import os
import sys
import argparse
import subprocess


def main(arguments):

    project_type = ''
    build_path = 'projects/default'

    parser = argparse.ArgumentParser(
        description="Generates project files",
        formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('-t', "--type", help="type options: [vs2019, xcode]")

    args = parser.parse_args(arguments)

    add_extra = False

    if args.type == "vs2019":
        project_type = 'Visual Studio 16 2019'
        build_path = 'projects/VS'
        add_extra = True

    if args.type == "xcode":
        project_type = 'Xcode'
        build_path = 'projects/xcode'
        add_extra = True

    if sys.platform.startswith('win'):
        shell = True
    else:
        shell = False

    cmakeCmd = ['cmake', '-B', build_path]
    
    if add_extra:
        cmakeCmd += ['-G', project_type]
    
    print ("Generating...")

    subprocess.check_call(cmakeCmd, stderr=subprocess.STDOUT, shell=shell)

    print ("Done.")


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
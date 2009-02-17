#!/usr/bin/python
import  os, sys, optparse
sys.path.insert( 0, os.path.abspath("libs"))

import dep_check
import fetch_repos
import windows_build
import linux_build

def parse_cmd_args():
    parser = optparse.OptionParser(version="%prog 1.0")
    
    parser.add_option("--mangos-destdir", "--install", "--destdir",
        action="store",
        dest="mangos_destdir",
        default="/opt/mangos")

    parser.add_option("--sd2-patch", "--patch", "--sd2", 
        action="store",
        dest="sd2_patch",
        default="MaNGOS-2008-12-22-ScriptDev2.patch")

    (options, args) = parser.parse_args()
    return options

if __name__ == '__main__':
    build_dir = os.getcwd()
    opts = parse_cmd_args()
    if os.name == "nt":
        dep_check.win32()
    else:
        dep_check.linux()

    fetch_repos.pre_build_fetch(opts)
    if os.name == "nt":
        windows_build.make()
        windows_build.install()
    else:
        linux_build.make(opts)
    os.chdir(build_dir)
    fetch_repos.post_build_fetch()


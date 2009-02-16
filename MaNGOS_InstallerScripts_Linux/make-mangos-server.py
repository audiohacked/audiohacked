#!/usr/bin/python
import  os, optparse

import fetch_repos
import windows_build
import linux_build

def parse_cmd_args():
    parser = optparse.OptionParser(version="%prog 1.0")
    
    parser.add_option("--mangos-destdir", "--install", "--destdir"
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
    fetch_repos.pre_build_fetch()
    if os.name == "nt":
        windows_build.make()
        windows_build.install()
    else:
        linux_build.make(build_dir, opts)
    fetch_repos.post_build_fetch()


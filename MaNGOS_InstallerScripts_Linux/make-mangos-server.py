#!/usr/bin/python
import re, os, sys, subprocess
import optparse

def check_for_dependencies():
    print "Checking for Dependencies"

def parse_cmd_args():
    parser = optparse.OptionParser(version="%prog 1.0")
    
    parser.add_option("--mangos",
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
    my_args = parse_cmd_args()
    print (my_args)
    if os.path.exists("mangos"):
        os.path.chdir("mangos")
        os.system("git pull -u")
    else:
        print "MaNGOS is not present; checking out MaNGOS"
        subprocess.call("git clone git://github.com/mangos/mangos.git")
        os.path.chdir("mangos")

    if os.path.exists("src/bindings/ScriptDev2"):
        subprocess.call("svn up src/bindings/ScriptDev2")
    else:
        print "ScriptDev2 is not present; checking out Mangos"
        subprocess.call("mkdir src/bindings/ScriptDev2")
        subprocess.call("svn co https://scriptdev2.svn.sourceforge.net/svnroot/scriptdev2 src/bindings/ScriptDev2")
        subprocess.call("git apply src/bindings/ScriptDev2/patches/"+my_args.sd2_path)

    if os.name == "nt"
        print "Running On Windows NT"
    else:
        if os.path.exists("objdir"):
            subprocess.call("rm -rf objdir")
        subprocess.call("autoreconf --install --force")
        subprocess.call("aclocal")
        subprocess.call("autoheader")
        subprocess.call("autoconf")
        subprocess.call("automake --add-missing")
        subprocess.call("automake src/bindings/ScriptDev2/Makefile")

        subprocess.call("mkdir objdir")
        os.path.chdir("objdir")
        subprocess.call("../configure ",
            "--prefix=",my_args.mangos_destdir,
            "--sysconfdir=",my_args.mangos_destdir,"/etc ",
            "--enable-cli --enable-ra ",
            "--datadir=",my_args)
        subprocess.call("make")
        os.path.chdir("../..")
        
        if os.path.exists("sd2-acid"):
        	subprocess.call("svn up sd2-acid")
        else:
        	subprocess.call("svn co https://sd2-acid.svn.sourceforge.net/svnroot/sd2-acid")

        if os.path.exists("unifieddb"):
            subprocess.call("svn up unifieddb")
        else:
        	subprocess.call("svn co https://unifieddb.svn.sourceforge.net/svnroot/unifieddb/trunk unifieddb")

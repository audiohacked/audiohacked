#!/usr/bin/python
import  re, os, sys, subprocess, optparse, shutil
import pysvn

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
    svn_client = pysvn.Client()
    my_args = parse_cmd_args()
    if os.path.exists("C:\\Program Files\\Git"):
        proc_git = subprocess.Popen("C:\\Program Files\\Git\\bin\\wish.exe C:\\Program Files\\Git\\libexec\\git-core\\git-gui", shell=True)

    if os.path.exists("mangos"):
        print ("Updating MaNGOS sourcecode")
        os.chdir("mangos")
        #os.system("git pull -u")
        git_python.
    else:
        print ("MaNGOS is not present; checking out MaNGOS")
        #subprocess.call("git clone git://github.com/mangos/mangos.git")
        os.chdir("mangos")

    if os.path.exists("src/bindings/ScriptDev2"):
        print ("Updating ScriptDev2 sourcecode")
        #subprocess.call("svn up src/bindings/ScriptDev2")
        svn_client.update('./src/bindings/ScriptDev2')
        
    else:
        print ("ScriptDev2 is not present; checking out ScriptDev2")
        os.mkdir("src/bindings/ScriptDev2")
        #subprocess.call("svn co https://scriptdev2.svn.sourceforge.net/svnroot/scriptdev2 src/bindings/ScriptDev2")
        svn_client.checkout('https://scriptdev2.svn.sourceforge.net/svnroot/scriptdev2', 'src/bindings/ScriptDev2')
        #subprocess.call("git apply src/bindings/ScriptDev2/patches/"+my_args.sd2_path)

    if os.name == "nt":
        prog_git = None

        if os.path.exists("C:\\Program Files\\Microsoft Visual Studio 9.0"):
            print ("Building...")
            p = subprocess.Popen("C:\\Program Files\\Microsoft Visual Studio 9.0\\VC\\vcvarsall.bat x86", shell=True)
            p.communicate("msbuild win/mangosdVC90.sln /p:Configuration=Release")
            p.communicate("msbuild src/bindings/ScriptDev2/scriptVC90.sln /p:Configuration=Release")
        if os.path.exists("bin\Win32_Release"):
            print ("Installing...")
            shutil.copytree("bin\\Win32_Release", "C:\\MaNGOS", ignore=shutil.ignore_patterns('*.map', '*.pdb', '*.exp'))
            shutil.copyfile("src/mangosd/mangosd.conf.dist.in", "C:/MaNGOS/mangosd.conf.dist")
            shutil.copyfile("src/mangosd/mangosd.conf.dist.in", "C:/MaNGOS/mangosd.conf")
            shutil.copyfile("src/realmd/realmd.conf.dist.in", "C:/MaNGOS/realmd.conf.dist")
            shutil.copyfile("src/realmd/realmd.conf.dist.in", "C:/MaNGOS/realmd.conf")
        
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
        os.chdir("objdir")
        subprocess.call("../configure ",
            "--prefix=",my_args.mangos_destdir,
            "--sysconfdir=",my_args.mangos_destdir,"/etc ",
            "--enable-cli --enable-ra ",
            "--datadir=",my_args)
        subprocess.call("make")
        os.chdir("../..")
        
        if os.path.exists("sd2-acid"):
        	subprocess.call("svn up sd2-acid")
        else:
        	subprocess.call("svn co https://sd2-acid.svn.sourceforge.net/svnroot/sd2-acid")

        if os.path.exists("unifieddb"):
            subprocess.call("svn up unifieddb")
        else:
        	subprocess.call("svn co https://unifieddb.svn.sourceforge.net/svnroot/unifieddb/trunk unifieddb")

#!/usr/bin/python
import  re, os, sys, subprocess, optparse, shutil
import pysvn
import gitshelve

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
    build_dir = os.getcwd()
    svn_client = pysvn.Client()
    my_args = parse_cmd_args()

    if os.path.exists("C:\\Program Files\\Git"):
        proc_git = subprocess.call("C:\\Program Files\\Git\\bin\\wish.exe C:\\Program Files\\Git\\libexec\\git-core\\git-gui", shell=True)

    if os.path.exists("mangos"):
        print ("Updating MaNGOS sourcecode")
        os.chdir("mangos")
        #subprocess.call("git pull -u", shell=True)
        gitshelve.git('pull', '-u')
    else:
        print ("MaNGOS is not present; checking out MaNGOS")
        #subprocess.call("git clone git://github.com/mangos/mangos.git", shell=True)
        gitshelve.git('clone', 'git://github.com/mangos/mangos.git')
        os.chdir("mangos")

    if os.path.exists("src/bindings/ScriptDev2"):
        print ("Updating ScriptDev2 sourcecode")
        svn_client.update('./src/bindings/ScriptDev2')
        
    else:
        print ("ScriptDev2 is not present; checking out ScriptDev2")
        os.mkdir("src/bindings/ScriptDev2")
        svn_client.checkout('https://scriptdev2.svn.sourceforge.net/svnroot/scriptdev2', 'src/bindings/ScriptDev2')
        #subprocess.call("git apply src/bindings/ScriptDev2/patches/"+my_args.sd2_patch, shell=True)
        gitshelve.git('apply', 'src/bindings/ScriptDev2/patches/'+my_args.sd2_patch)

    if os.name == "nt":
        if os.path.exists("C:\\Program Files\\Microsoft Visual Studio 9.0"):
            print ("Building...")
            p = subprocess.Popen("C:\\Program Files\\Microsoft Visual Studio 9.0\\VC\\vcvarsall.bat x86", shell=True)
            p.communicate("msbuild win\\mangosdVC90.sln /p:Configuration=Release")
            p.communicate("msbuild src\\bindings\\ScriptDev2\\scriptVC90.sln /p:Configuration=Release")
        if os.path.exists("bin\\Win32_Release"):
            print ("Installing...")
            shutil.copytree("bin\\Win32_Release", "C:\\MaNGOS", ignore=shutil.ignore_patterns('*.map', '*.pdb', '*.exp'))
            shutil.copyfile("src\\mangosd\\mangosd.conf.dist.in", "C:\\MaNGOS\\mangosd.conf.dist")
            shutil.copyfile("src\\mangosd\\mangosd.conf.dist.in", "C:\\MaNGOS\\mangosd.conf")
            shutil.copyfile("src\\realmd\\realmd.conf.dist.in", "C:\\MaNGOS\\realmd.conf.dist")
            shutil.copyfile("src\\realmd\\realmd.conf.dist.in", "C:\\MaNGOS\\realmd.conf")
        
    else:

        if os.path.exists("objdir"):
            shutil.rmtree("objdir", ignore_errors=True)
        
        subprocess.call("autoreconf --install --force", shell=True)
        subprocess.call("aclocal", shell=True)
        subprocess.call("autoheader", shell=True)
        subprocess.call("autoconf", shell=True)
        subprocess.call("automake --add-missing", shell=True)
        subprocess.call("automake src/bindings/ScriptDev2/Makefile", shell=True)
        os.mkdir("objdir")
        os.chdir("objdir")

        subprocess.call("../configure"+" --enable-cli --enable-ra"+
            "--prefix="+my_args.mangos_destdir+" --sysconfdir="+my_args.mangos_destdir+"/etc"+
            "--datadir="+my_args.mangos_destdir, shell=True)
        
        subprocess.call("make", shell=True)
        os.chdir(build_dir)

        if os.path.exists("sd2-acid"):
            print ("Updating ACID sourcecode")
            svn_client.update('./sd2-acid')
        else:
            print ("ACID is not present; checking out ACID")
            svn_client.checkout('https://sd2-acid.svn.sourceforge.net/svnroot/sd2-acid', './sd2-acid')

        if os.path.exists("unifieddb"):
            print ("Updating UDB sourcecode")
            svn_client.update('./unifieddb')
        else:
            print ("UDB is not present; checking out UDB")
            svn_client.checkout('https://unifieddb.svn.sourceforge.net/svnroot/unifieddb/trunk', './unifieddb')



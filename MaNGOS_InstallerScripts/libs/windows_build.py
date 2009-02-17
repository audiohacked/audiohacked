import  os, sys, subprocess, shutil
import dep_check

def make():
    if os.path.exists(dep_check.vs_install_dir):
        print ("Building...")
        print "current dir: "+os.getcwd()

        if os.path.basename(os.getcwd()) != "mangos":
            os.chdir("mangos")
            
        try:
            mangos = subprocess.call("msbuild win\\mangosdVC90.sln /p:Configuration=Release", shell=True, env=os.environ)
            if mangos < 0:
                print >>sys.stderr, "Child was terminated by signal", -mangos
            elif mangos > 0:
                print >>sys.stderr, "Child returned", mangos
        except OSError, e:
            print >>sys.stderr, "Execution failed:", e
        try:
            sd2 = subprocess.call("msbuild src\\bindings\\ScriptDev2\\scriptVC90.sln /p:Configuration=Release", shell=True, env=os.environ)
            if sd2 < 0:
                print >>sys.stderr, "Child was terminated by signal", -sd2
            elif sd2 > 0:
                print >>sys.stderr, "Child returned", sd2
        except OSError, e:
            print >>sys.stderr, "Execution failed:", e
            

def install():
    if os.path.exists("bin\\Win32_Release"):
        print ("Installing...")
        if os.path.exists("C:\\MaNGOS"):
            shutil.rmtree("C:\\MaNGOS", ignore_errors=True)
        shutil.copytree("bin\\Win32_Release", "C:\\MaNGOS", ignore=shutil.ignore_patterns('*.map', '*.pdb', '*.exp'))
        shutil.copyfile("src\\mangosd\\mangosd.conf.dist.in", "C:\\MaNGOS\\mangosd.conf.dist")
        if not os.path.exists("C:\\MaNGOS\\mangosd.conf"):
            shutil.copyfile("src\\mangosd\\mangosd.conf.dist.in", "C:\\MaNGOS\\mangosd.conf")
        shutil.copyfile("src\\realmd\\realmd.conf.dist.in", "C:\\MaNGOS\\realmd.conf.dist")
        if not os.path.exists("C:\\MaNGOS\\realmd.conf"):
            shutil.copyfile("src\\realmd\\realmd.conf.dist.in", "C:\\MaNGOS\\realmd.conf")
        shutil.copyfile("src\\bindings\\ScriptDev2\\scriptdev2.conf.dist.in", "C:\\MaNGOS\\scriptdev2.conf.dist")
        if not os.path.exists("C:\\MaNGOS\\scriptdev2.conf"):
            shutil.copyfile("src\\bindings\\ScriptDev2\\scriptdev2.conf.dist.in", "C:\\MaNGOS\\scriptdev2.conf")

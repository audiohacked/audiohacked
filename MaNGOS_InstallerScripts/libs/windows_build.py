import  os, sys, subprocess, shutil, fnmatch

def make():
    print ("Building...")
    #print "current dir: "+os.getcwd()

    if os.path.basename(os.getcwd()) != "mangos":
        os.chdir("mangos")
        
    try:
        mangos = subprocess.call("msbuild win\\mangosdVC90.sln /p:Configuration=Release", shell=True)
        if mangos < 0:
            print >>sys.stderr, "Child was terminated by signal", -mangos
        elif mangos > 0:
            print >>sys.stderr, "Child returned", mangos
    except OSError, e:
        print >>sys.stderr, "Execution failed:", e
    try:
        sd2 = subprocess.call("msbuild src\\bindings\\ScriptDev2\\scriptVC90.sln /p:Configuration=Release", shell=True)
        if sd2 < 0:
            print >>sys.stderr, "Child was terminated by signal", -sd2
        elif sd2 > 0:
            print >>sys.stderr, "Child returned", sd2
    except OSError, e:
        print >>sys.stderr, "Execution failed:", e

def install(opts):
    if os.path.exists("bin\\Win32_Release"):
        print ("Installing...")
        if os.path.exists(opts.mangos_destdir):
            for name in os.listdir("bin\\Win32_Release"):
                if fnmatch.fnmatch(name, '*.map'):
                    pass
                elif fnmatch.fnmatch(name, '*.pdb'):
                    pass
                elif fnmatch.fnmatch(name, '*.exp'):
                    pass
                else:
                    srcname = os.path.join("bin\\Win32_Release", name)
                    destname = os.path.join(opts.mangos_destdir, name)
                    shutil.copy2(srcname, destname)
        else:
            shutil.copytree("bin\\Win32_Release", opts.mangos_destdir, ignore=shutil.ignore_patterns('*.map', '*.pdb', '*.exp'))

        shutil.copyfile("src\\mangosd\\mangosd.conf.dist.in", opts.mangos_destdir+"\\mangosd.conf.dist")
        if not os.path.exists(opts.mangos_destdir+"\\mangosd.conf"):
            shutil.copyfile("src\\mangosd\\mangosd.conf.dist.in", opts.mangos_destdir+"\\mangosd.conf")
        shutil.copyfile("src\\realmd\\realmd.conf.dist.in", opts.mangos_destdir+"\\realmd.conf.dist")
        if not os.path.exists(opts.mangos_destdir+"\\realmd.conf"):
            shutil.copyfile("src\\realmd\\realmd.conf.dist.in", opts.mangos_destdir+"\\realmd.conf")
        shutil.copyfile("src\\bindings\\ScriptDev2\\scriptdev2.conf.dist.in", opts.mangos_destdir+"\\scriptdev2.conf.dist")
        if not os.path.exists(opts.mangos_destdir+"\\scriptdev2.conf"):
            shutil.copyfile("src\\bindings\\ScriptDev2\\scriptdev2.conf.dist.in", opts.mangos_destdir+"\\scriptdev2.conf")

if __name__ == '__main__':
    os.chdir("..\\mangos")

import  os, subprocess, shutil

def make(home, make_opts):
    if os.path.basename(os.getcwd()) != "mangos":
        os.chdir("mangos")

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

    subprocess.call(["../configure --enable-cli --enable-ra",
        "--prefix="+make_opts.mangos_destdir,
        "--sysconfdir="+make_opts.mangos_destdir+"/etc",
        "--datadir="+make_opts.mangos_destdir], shell=True)
    
    subprocess.call("make", shell=True)
    os.chdir(home)

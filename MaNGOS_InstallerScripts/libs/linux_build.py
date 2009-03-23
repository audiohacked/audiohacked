import  os, subprocess, shutil

def make(make_opts):
    print "Install Dir: ", make_opts.mangos_destdir
    if make_opts.debug: print "Current Dir: ", os.getcwd()
    if os.path.basename(os.getcwd()) != "mangos":
        os.chdir("mangos")
    if make_opts.debug: print "Current Dir: ", os.getcwd()
    if os.path.exists("objdir"):
        shutil.rmtree("objdir", ignore_errors=True)
    if make_opts.rebuild:
        subprocess.call("autoreconf --install --force", shell=True)
        subprocess.call("aclocal", shell=True)
        subprocess.call("autoheader", shell=True)
        subprocess.call("autoconf", shell=True)
        subprocess.call("automake --add-missing", shell=True)
        subprocess.call("automake src/bindings/ScriptDev2/Makefile", shell=True)
    os.mkdir("objdir")
    os.chdir("objdir")
    if make_opts.debug: print "Current Dir: ", os.getcwd()

    config_cmd = ["../configure --enable-cli --enable-ra",
    	"--prefix="+make_opts.mangos_destdir,
        "--sysconfdir="+make_opts.mangos_destdir+"/etc",
	"--datadir="+make_opts.mangos_destdir]
    #print " ".join(config_cmd)
    subprocess.call(" ".join(config_cmd), shell=True)
    subprocess.call("make", shell=True)

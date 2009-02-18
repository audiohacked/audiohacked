import os, sys
import windows_registry

vs_install_dir = "C:\\Program Files\\Microsoft Visual Studio 9.0"
python25_install_dir = "C:\\Python25"
python26_install_dir = "C:\\Python26"
frameworkdir = "C:\\Windows\\Microsoft.NET\\Framework"
git_install_dir = "C:\\Program Files\\Git"

def win32():
    print "Checking for Dependencies"

    try:
        import pysvn
        print "---Found PySVN"
    except ImportError:
        print "---PySVN Not Found, Please Install"
        sys.exit(1)
        
##    if os.path.exists(windows_registry.find_python()):
##            print "---Found Python"
##            os.environ['path'] += ";"+path
##            break
##    else:
##        print "---Python 2.5 or 2.6 not found"
##        sys.exit(1)

    if os.path.exists(git_install_dir):
        print "---Found Git"
        os.environ['path'] += ";"+git_install_dir+"\\bin;"
    else:
        print "---Git Not Found"
        sys.exit(1)

    vs_path = windows_registry.get_visualstudio2008()
    if os.path.exists(vs_path):
        print "---Found Visual Studio 9"
        sdk_path = find_MSPlatformSDK() 
        if sdk_path == None:
            sdk_path = vs_path+"\\VC\\PlatformSDK"

        path = vs_path+"\\Common7\\IDE;"+vs_path+"\\VC\\BIN;"
              +vs_path+"\\Common7\\Tools;"+frameworkdir+"\\v3.5;"
              +frameworkdir+"\\v2.0.50727;"+vs_path+"\\VC\\VCPackages;"
              +sdk_path+"\\bin;"
        include = vs_install_dir+"\\VC\\INCLUDE;"+sdk_path+"\\include;"
        lib = vs_install_dir+"\\VC\\LIB;"+sdk_path+"\\lib;"
        libpath = frameworkdir+"\\v3.5;"+frameworkdir+"\\v2.0.50727;"
                 +vs_install_dir+"\\VC\\LIB;"

        old_path = os.environ['path']
        os.environ['path'] = path+old_path
        os.environ['include'] = include
        os.environ['lib'] = lib
        os.environ['libpath'] = libpath
    else:
        print "---Visual Studio 9 Not Found"
        sys.exit(1)

def which(program):
    def is_exe(fpath):
        return os.path.exists(fpath) and os.access(fpath, os.X_OK)
    fpath, fname = os.path.split(program)
    if fpath:
        if is_exe(program):
            return program
    else:
        for path in os.environ["PATH"].split(os.pathsep):
            exe_file = os.path.join(path, program)
            if is_exe(exe_file):
                return exe_file
    return None

def linux():
    print "Checking for Dependencies"
    try:
        import pysvn
        print "---Found PySVN"
    except ImportError:
        print "---PySVN Not Found, Please Install"
        sys.exit(1)

    if os.path.basename(which("git")) == "git":
        print "---Found Git"
    else:
        print "---Git Not Found" 

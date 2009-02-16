import os

vs_install_dir = "C:\\Program Files\\Microsoft Visual Studio 9.0"
python25_install_dir = "C:\\Python25"
python26_install_dir = "C:\\Python26"
git_install_dir = "C:\\Program Files\\Git"

def check_for_deps_win32():
    print "Checking for Dependencies"

    if os.path.exists(python25_install_dir):
        print "---Found Python 2.5"
        os.environ['path'] += ";C:\\Python25"
    elif os.path.exists(python26_install_dir):
        print "---Found Python 2.6"
        os.environ['path'] += ";C:\\Python26"
    else:
        print "---Python 2.5 or 2.6 not found"

    if os.path.exists(git_install_dir):
        print "---Found Git"
        os.environ['path'] += ";"+git_install_dir+"\\bin;"+git_install_dir+"\\mingw\\bin"
    else:
        print "---Git Not Found"

    if os.path.exists("C:\\Program Files\\Microsoft Visual Studio 9.0"):
        print "---Found Visual Studio 9"
        old_path = os.environ['path']
        #old_include = os.environ['include']
        #old_lib = os.environ['lib']
        #old_libpath = os.environ['libpath']
        
        path = vs_install_dir+"\\Common7\\IDE;"
        path += vs_install_dir+"\\VC\\BIN;"
        path += vs_install_dir+"\\Common7\\Tools;"
        path += "C:\\Windows\\Microsoft.NET\\Framework\\v3.5;"
        path += "C:\\Windows\Microsoft.NET\\Framework\\v2.0.50727;"
        path += vs_install_dir+"\\VC\\VCPackages;"

        path += "C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0A\\bin;"
        path += vs_install_dir+"\\VC\\PlatformSDK;"
        os.environ['path'] = path+old_path

        include = vs_install_dir+"\\VC\\INCLUDE;"
        include += "C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0A\\include;"
        include += vs_install_dir+"\\VC\\PlatformSDK\\include;"
        os.environ['include'] = include

        lib = vs_install_dir+"\\VC\\LIB;"
        lib += "C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0A\\lib;"
        lib += vs_install_dir+"\\VC\\PlatformSDK\\lib;"
        os.environ['lib'] = lib

        libpath = "C:\\Windows\\Microsoft.NET\\Framework\\v3.5;"
        libpath += "C:\\Windows\\Microsoft.NET\\Framework\\v2.0.50727;"
        libpath += vs_install_dir+"\\VC\\LIB;"
        os.environ['libpath'] = libpath
    else:
        print "---Visual Studio 9 Not Found"

def check_for_deps_linux():
    print "Checking for Dependencies"

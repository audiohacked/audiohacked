import os, sys, subprocess

frameworkdir = "C:\\Windows\\Microsoft.NET\\Framework\\"
git_install_dir = "C:\\Program Files\\Git"

def win32():
	if os.name == "nt":
		import windows_registry
	else:
		print "You are trying to run the windows dep checker on a non-Windows system"
		sys.exit(1)
	print "Checking for Dependencies"
	python_path = windows_registry.find_python()
	vs_path = windows_registry.find_visualstudio2008()
	sdk_path = windows_registry.find_MSPlatformSDK() 
	try:
		import pysvn
		print "---Found PySVN"
	except ImportError:
		print "---PySVN Not Found, Please Install"
		sys.exit(1)

	if os.path.exists(git_install_dir):
		print "---Found Git"
		os.environ['path'] += ";"+git_install_dir+"\\bin;"
	else:
		print "---Git Not Found"
		sys.exit(1)

	try:	
		if os.path.exists(python_path):
				print "---Found Python"
				os.environ['path'] += ";"+python_path+";"+python_path+"Scripts;"
	except TypeError:
		print "---Python 2.5 or 2.6 not found"
		sys.exit(1)

	try:
		import _mysql
		print "---Found PyMySQL"
	except ImportError:
		print "---PyMySQL Not Found, Build Now!"
		os.chdir("libs\\MySQLdb")
		subprocess.call("ez_setup.py -U setuptools", shell=True, stdout=sys.stdout)
		subprocess.call("easy_install .", shell=True, stdout=sys.stdout)
		subprocess.call("easy_install .", shell=True, stdout=sys.stdout)
		subprocess.call("easy_install .", shell=True, stdout=sys.stdout)
		os.chdir("..\\..")

	try:
		if os.path.exists(vs_path):
			print "---Found Visual Studio 9"
			if sdk_path == "":
				sdk_path = vs_path+"VC\\PlatformSDK\\"

			path = vs_path+"Common7\\IDE;"+vs_path+"VC\\BIN;"
			path += vs_path+"Common7\\Tools;"+frameworkdir+"v3.5;"
			path += frameworkdir+"v2.0.50727;"+vs_path+"VC\\VCPackages;"
			path += sdk_path+"bin;"
			include = vs_path+"VC\\INCLUDE;"+sdk_path+"include;"
			lib = vs_path+"VC\\LIB;"+sdk_path+"lib;"
			libpath = frameworkdir+"v3.5;"+frameworkdir+"v2.0.50727;"
			libpath += vs_path+"VC\\LIB;"
			old_path = os.environ['path']
			os.environ['path'] = path+old_path
			os.environ['include'] = include
			os.environ['lib'] = lib
			os.environ['libpath'] = libpath
	except TypeError:
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

if __name__ == '__main__':
	win32()

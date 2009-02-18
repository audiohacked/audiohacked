import sys
import _winreg

#vs2008_regpath = "SOFTWARE\\Microsoft\\VCExpress\\9.0\\"
vs2008_regpath = "SOFTWARE\\Microsoft\\VisualStudio\\SxS\\VS7\\"
python_regpath = "SOFTWARE\\Python\\PythonCore\\%s\\" % (sys.version[:3])
platformsdk_regpath = "SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows\\"

pythonpath = "%s;%s\\Lib\\;%s\\DLLs\\" % (
    sys.prefix, sys.prefix, sys.prefix
)

def find_python():
    with _winreg.OpenKey(_winreg.HKEY_LOCAL_MACHINE, python_regpath) as key:
        try:
            return _winreg.QueryValue(key, "InstallPath")
        except WindowsError:
            return ""
            

def find_visualstudio2008():
    with _winreg.OpenKey(_winreg.HKEY_LOCAL_MACHINE, vs2008_regpath) as key:
        try:
            return _winreg.QueryValueEx(key, "9.0")[0]
        except WindowsError:
            return ""

def find_MSPlatformSDK():
    with _winreg.OpenKey(_winreg.HKEY_LOCAL_MACHINE, platformsdk_regpath) as key:
        try:
            return _winreg.QueryValueEx(key, "CurrentInstallFolder")[0]
        except WindowsError:
            return ""
    
#def find_git():
#    with _winreg.OpenKey(HKEY_LOCAL_MACHINE, "\\SOFTWARE\\") as key:
#        print _winreg.QueryValue(key, "")
    
if __name__ == '__main__':
    print find_python()
    print find_visualstudio2008()
    print find_MSPlatformSDK()

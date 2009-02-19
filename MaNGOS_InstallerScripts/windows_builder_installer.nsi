; (c) Sean Nelson <snelson@nmt.edu>

;--------------------------------
;Include Modern UI

    !include "MUI2.nsh"
    !include "InstallOptions.nsh"

;--------------------------------
;General

    ;Name, File, Compression, and InstallerBranding
    SetCompressor LZMA
    Name "MaNGOS Auto-Installer for Windows"
    OutFile "windows_mangos_installer.exe"
    BrandingText "(c) Sean Nelson <snelson@nmt.edu>"

    ;Default Installation Folder
    InstallDir "C:\MaNGOS"
    
    ;Get installation folder from registry if available
    InstallDirRegKey HKCU "Software\MaNGOS" ""
    
    ;Request application privileges for Windows Vista
    RequestExecutionLevel user

    ;Variables
    Var sql_path
    Var sql_version
    ;Var sql_script
    Var python_path
    Var python_version
    Var login
    Var password
    Var vs2008_path
    Var sdk_path


;--------------------------------
;Interface Settings

    !define MUI_ABORTWARNING

;--------------------------------
;Language Selection Dialog Settings

    ;Remember the installer language
    !define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
    !define MUI_LANGDLL_REGISTRY_KEY "Software\Modern UI Test" 
    !define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"

;--------------------------------
;Pages

    !insertmacro MUI_PAGE_WELCOME
    ;!insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt"
    !insertmacro MUI_PAGE_COMPONENTS
    !insertmacro MUI_PAGE_DIRECTORY
    Page custom GetInfos "" ": Information page"
    !insertmacro MUI_PAGE_INSTFILES
    
    !insertmacro MUI_UNPAGE_CONFIRM
    !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages
    
    !insertmacro MUI_LANGUAGE "English"
    !insertmacro MUI_LANGUAGE "German"
    !insertmacro MUI_LANGUAGE "French"

;--------------------------------
;Installer Functions
    
    Function .onInit
    
        System::Call 'kernel32::CreateMutexA(i 0, i 0, t "Audiohacked_MaNGOS") i .r1 ?e'
        Pop $R0
        
        StrCmp $R0 0 +3
            MessageBox MB_OK|MB_ICONEXCLAMATION "The installer is already running."
            Abort

        !insertmacro MUI_LANGDLL_DISPLAY

        InitPluginsDir
        !insertmacro INSTALLOPTIONS_EXTRACT "custom.ini"    

    FunctionEnd
    
    ;Function .onInstSuccess
    ;FunctionEnd
    
    ;Function .onGUIEnd
    ;FunctionEnd

    Function GetInfos 
        !insertmacro MUI_HEADER_TEXT "Database informations" "Database informations - please fill all elements"
        !insertmacro INSTALLOPTIONS_DISPLAY "custom.ini"
    FunctionEnd

;--------------------------------
;Descriptions
    
    ;USE A LANGUAGE STRING IF YOU WANT YOUR DESCRIPTIONS TO BE LANGAUGE SPECIFIC
    
    ;Assign descriptions to sections
    ;!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    ;    !insertmacro MUI_DESCRIPTION_TEXT ${DepCheckSec} "A test section."
    ;!insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Installer Sections

InstType "Full"
InstType "Minimal"
InstType "DB Install Only"

Section "Dependency Checks" DepCheckSec
    SectionIn 1 2
    ; Visual Studio 2008
    ReadRegStr $vs2008_path HKLM "Software\Microsoft\VisualStudio\SxS\VS7" "9.0" 
    ;messageBox MB_OK "VS2008 Path: $vs2008_path"
    
    ; Microsoft Platform SDK
    ReadRegStr $sdk_path HKLM "Software\Microsoft\Microsoft SDKs\Windows" "CurrentInstallFolder" 
    ;messageBox MB_OK "Platform SDK Path: $sdk_path"

    ; Python 2.6
    ReadRegStr $python_path HKLM "Software\Python\PythonCore\2.6\InstallPath" ""
    ReadRegStr $python_version HKLM "Software\Python\PythonCore\2.6\InstallPath\InstallGroup" ""
    ;messageBox MB_OK "Python $python_version Path: $python_path"

    
    ; MySQL 5.1 Server
    ReadRegStr $sql_path HKLM "Software\MySQL AB\Mysql Server 5.1" "Location"
    ReadRegStr $sql_version HKLM "Software\MySQL AB\Mysql Server 5.1" "Version"
    ;messageBox MB_OK "MySQL Server $sql_version Path: $sql_path"
    
    ; SVN
    ; check if svn is installed
    
    ; Git
    ; check if git is installed
SectionEnd

Section "Fetch Sources" FetchSec
    SectionIn 1 2
    ;   git clone git://github.com/mangos/mangos.git
    ;   mkdir src/bindings/ScriptDev2
    ;   svn co https://scriptdev2.svn.sourceforge.net/svnroot/scriptdev2 src/bindings/ScriptDev2
    ;   git apply src/bindings/ScrtipDev2/patches/MaNGOS_
    ;   svn co https://sd2-acid.svn.sourceforge.net/svnroot/sd2-acid sd2-acid
    ;   svn co https://unifieddb.svn.sourceforge.net/svnroot/unifieddb/trunk unifieddb
SectionEnd

Section "Build Server" BuildSec
    SectionIn 1 2
    ; msbuild win\mangosdVC90.sln /p:Configuration=Release
    ; msbuild src\bindings\ScriptDev2\scriptVC90.sln /p:Configuration=Release
SectionEnd

Section "Install Server" InstServerSec
    SectionIn 1 2
    SetOutPath "$INSTDIR"
    
    ;ADD FIIES TO INSTALL
    
    ;Store installation folder
    WriteRegStr HKCU "Software\MaNGOS" "" $INSTDIR
    
    ;Create uninstaller
    WriteUninstaller "$INSTDIR\Uninstall.exe"
    
    # create a shortcut named "new shortcut" in the start menu programs directory
    # point the new shortcut at the program uninstaller
    createShortCut "$SMPROGRAMS\new shortcut.lnk" "$INSTDIR\uninstall.exe"

SectionEnd

Section "Install DB" InstDatabaseSec
    SectionIn 1 3
    ; Install MaNGOS/UDB Database
    ReadINIStr $login "$PLUGINSDIR\custom.ini" "Field 2" "State"
    ReadINIStr $password "$PLUGINSDIR\custom.ini" "Field 4" "State"

    ; ExecWait '"$sql_path\bin\mysql.exe" -u $login -p $password < $sql_script'
    ;messageBox MB_OK "username: $login, passwd: $password"
SectionEnd

Section "Uninstall"
    
    ;ADD YOUR OWN FILES HERE...
    
    Delete "$INSTDIR\Uninstall.exe"
    
    Delete "$SMPROGRAMS\new shortcut.lnk"
    
    ;RMDir "$INSTDIR"
    
    DeleteRegKey /ifempty HKCU "Software\MaNGOS"
    
SectionEnd
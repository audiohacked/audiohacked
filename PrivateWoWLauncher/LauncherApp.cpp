#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#	include "wx/wx.h"
#endif

#ifdef WIN32
	#include <wx/msw/registry.h>
#endif

#include "LauncherApp.h"
#include "LauncherFrame.h"

IMPLEMENT_APP(LauncherApp)

bool LauncherApp::OnInit()
{
	Find_WoW_Path();
	LauncherFrame *frame = new LauncherFrame(wxString::FromAscii("RealmList Launcher"), wxDefaultPosition, wxDefaultSize);
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

int LauncherApp::OnExit()
{
	wxApp::CleanUp();
	return 0;
}

void LauncherApp::Find_WoW_Path(void)
{
	#ifdef WIN32
		wow_path = Win32Registry_Find_WoW();
	#else
		wow_path = wxString::FromAscii("/Applications/World of Warcraft/");
	#endif
}

#ifdef WIN32
wxString LauncherApp::Win32Registry_Find_WoW(void)
{
	wxString InstallKey = wxString::FromAscii("HKEY_LOCAL_MACHINE\\SOFTWARE\\Blizzard Entertainment\\World of Warcraft\\");
	wxRegKey *pRegKey = new wxRegKey(InstallKey);

	if( !pRegKey->Exists() )
	{
		return wxString();
	}
	else
	{
		wxString ClientPath;
		pRegKey->QueryValue("InstallPath", ClientPath);
		return ClientPath;
	}
}
#endif
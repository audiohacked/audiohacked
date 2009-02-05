#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#	include "wx/wx.h"
#endif

#ifdef __WIN32
	#include <wx/msw/registry.h>
#endif

#include "LauncherApp.h"
#include "LauncherFrame.h"

IMPLEMENT_APP(LauncherApp)

bool LauncherApp::OnInit()
{
	Find_WoW_Path();
	LauncherFrame *frame = new LauncherFrame(wxT("RealmList Launcher"));
	frame->CreateStatusBar();
	frame->SetStatusText(_T("2009 (C) Sean Nelson <snelson@nmt.edu>"));
	frame->Show(true);
	SetTopWindow(frame);
	return true;
}

void LauncherApp::Find_WoW_Path(void)
{
	#ifdef __WIN32
		wow_path = Win32Registry_Find_WoW();
	#else
		wow_path = wxString::FromAscii("/Applications/World of Warcraft");
	#endif
}

#ifdef __WIN32
wxString LauncherApp::Win32Registery_Find_WoW(void)
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
		pRegKey->QueryValue("InstallPath", &ClientPath);
		return ClientPath;
	}
}
#endif
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#	include "wx/wx.h"
#endif

#include "LauncherRegister.h"

wxString *LauncherRegistery(void)
{
	#include <wx/msw/registry.h>
	wxString InstallKey = wxString::FromAscii("HKEY_LOCAL_MACHINE\\SOFTWARE\\Blizzard Entertainment\\World of Warcraft\\");
	wxRegKey *pRegKey = new wxRegKey(InstallKey);

	//will create the Key if it does not exist
	if( !pRegKey->Exists() )
	{
		return NULL;
	}
	else
	{
		wxString ClientPath;
		pRegKey->QueryValue("InstallPath", &ClientPath);
		return &ClientPath;
	}
}

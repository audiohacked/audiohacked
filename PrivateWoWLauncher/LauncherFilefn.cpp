#include "wx/wxprec.h"
 
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/msgdlg.h>
#include <wx/dir.h>
#include <wx/filefn.h>
#include <wx/log.h>

#include "LauncherFilefn.h"

wxDirTraverseResult LauncherDeleteCache::OnFile(const wxString& filename)
{
	if(wxRemoveFile(filename))
	{
		wxLogMessage(wxString::FromAscii("deleting file: ")+filename);
	}
	else
	{
		wxLogMessage(wxString::FromAscii("unable to delete file: ")+filename);
	}
	return wxDIR_CONTINUE;
}

wxDirTraverseResult LauncherDeleteCache::OnDir(const wxString& dirname)
{
	/*wxDir dir(dirname);
	if (dir.HasFiles())
	{
		return wxDIR_CONTINUE;
	}
	else if (dir.HasSubDirs())
	{
		return wxDIR_CONTINUE;
	}*/
	if(wxRmdir(dirname))
	{
		wxLogMessage(wxString::FromAscii("deleting dir: ")+dirname);
	}
	else
	{
		wxLogMessage(wxString::FromAscii("unable to delete dir: ")+dirname);
	}
	return wxDIR_CONTINUE;
}

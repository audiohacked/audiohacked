#include "wx/wxprec.h"
 
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/msgdlg.h>
#include <wx/dir.h>
#include <wx/filefn.h>
//#include <wx/log.h>

#include "LauncherFilefn.h"

wxDirTraverseResult LauncherDeleteCache::OnFile(const wxString& filename)
{
  /*
	if(wxRemoveFile(filename))
	{
		wxLogMessage(wxString::FromAscii("deleting file: ")+filename);
	}
	else
	{
		wxLogMessage(wxString::FromAscii("unable to delete file: ")+filename);
	}
	*/
	wxRemoveFile(filename);
	return wxDIR_CONTINUE;
}

wxDirTraverseResult LauncherDeleteCache::OnDir(const wxString& dirname)
{
  /*
	if(wxRmdir(dirname))
	{
		wxLogMessage(wxString::FromAscii("deleting dir: ")+dirname);
	}
	else
	{
		wxLogMessage(wxString::FromAscii("unable to delete dir: ")+dirname);
	}
	*/
	wxRmdir(dirname);
	return wxDIR_CONTINUE;
}

void LauncherFilefn::DeleteCache(wxString path)
{
	wxArrayString paths;
	LauncherDeleteCache traverser(paths);
	wxDir cache(path);
	while(cache.HasSubDirs())
	{
		//cache.Traverse(traverser, wxEmptyString, wxDIR_FILES|wxDIR_DIRS);
		cache.Traverse(traverser);
	}
}
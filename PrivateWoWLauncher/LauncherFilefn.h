#ifndef INCLUDED_LAUNCHER_FILE_FN_H
#define INCLUDED_LAUNCHER_FILE_FN_H

#include <wx/dir.h>

class LauncherDeleteCache : public wxDirTraverser
{
public:
	LauncherDeleteCache::LauncherDeleteCache(wxArrayString& paths) : m_paths(paths) {}
	virtual wxDirTraverseResult OnFile(const wxString& filename);
	virtual wxDirTraverseResult OnDir(const wxString& dirname);

private:
	wxArrayString& m_paths;
};

#endif /* INCLUDED_LAUNCHER_FILE_FN_H */
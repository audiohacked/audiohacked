#ifndef INCLUDED_LAUNCHER_FILE_FN_H
#define INCLUDED_LAUNCHER_FILE_FN_H

class LauncherDeleteCacheTraverser : public wxDirTraverser
{
public:
	LauncherDeleteCacheTraverser(wxString& path) : m_path(path) {}
	virtual wxDirTraverseResult OnFile(const wxString& filename)
	{
		wxRemoveFile(filename);
		return wxDIR_CONTINUE;
	}

	virtual wxDirTraversResult OnDir(const wxString& dirname)
	{
		wxRmdir(dirname);
		return wxDIR_CONTINUE;
	}
};

class LauncherFilefn
{
public:
	void ClearCache(wxCommandEvent &event);

};

#endif /* INCLUDED_LAUNCHER_FILE_FN_H */
#ifndef INCLUDED_LAUNCHER_FRAME_H
#define INCLUDED_LAUNCHER_FRAME_H

enum
{
	BUTTON_PRIVATE = wxID_HIGHEST + 1,
	BUTTON_PRIVATE2,
	BUTTON_BLIZZARD,
	BUTTON_CACHE,
};

class LauncherFrame : public wxFrame
{
public:
	LauncherFrame(const wxChar *title);
	~LauncherFrame();
	void PrivateList(wxCommandEvent &event);
	void PrivateList2(wxCommandEvent &event);
	void BlizzardList(wxCommandEvent &event);
	void ClearCache(wxCommandEvent &event);
	LauncherApp *myapp;
	
protected:
	DECLARE_EVENT_TABLE()
};

#endif /* INCLUDED_LAUNCHER_FRAME_H */

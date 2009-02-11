#ifndef INCLUDED_LAUNCHER_FRAME_H
#define INCLUDED_LAUNCHER_FRAME_H

enum
{
	BUTTON_PRIVATE = wxID_HIGHEST + 1,
	BUTTON_PRIVATE2,
	BUTTON_BLIZZARD,
	BUTTON_CACHE,
	BUTTON_CUSTOM,
	TEXT_CUSTOM,
};

class LauncherFrame : public wxFrame
{
public:
	LauncherFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
	~LauncherFrame();

	void PrivateList(wxCommandEvent &event);
	void PrivateList2(wxCommandEvent &event);
	void BlizzardList(wxCommandEvent &event);
	void CustomList(wxCommandEvent &event);
	void ClearCache(wxCommandEvent &event);
	
protected:
	DECLARE_EVENT_TABLE()

private:
	LauncherApp *myapp;
	wxButton *PrivateRealmListButton;
	wxButton *Private2RealmListButton;
	wxButton *BlizzardRealmListButton;
	wxButton *CustomRealmListButton;
	wxTextCtrl *CustomRealmText;
	wxButton *ClearCacheButton;
};

#endif /* INCLUDED_LAUNCHER_FRAME_H */

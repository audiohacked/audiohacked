#ifndef INCLUDED_LAUNCHER_REALMLIST_PANEL_H
#define INCLUDED_LAUNCHER_REALMLIST_PANEL_H

#include "LauncherApp.h"

enum
{
	BUTTON_PRIVATE = wxID_HIGHEST + 1,
	BUTTON_PRIVATE2,
	BUTTON_BLIZZARD,
	BUTTON_CACHE,
	BUTTON_CUSTOM,
	TEXT_CUSTOM,
};

class LauncherRealmlistPanel : public wxPanel
{
public:
	LauncherRealmlistPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);
	~LauncherRealmlistPanel();

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

#endif /* INCLUDED_LAUNCHER_REALMLIST_PANEL_H */

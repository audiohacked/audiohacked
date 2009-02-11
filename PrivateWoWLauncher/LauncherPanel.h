#ifndef INCLUDED_LAUNCHER_PANEL_H
#define INCLUDED_LAUNCHER_PANEL_H

#include <wx/notebook.h>

enum
{
	BUTTON_SWITCHER = wxID_HIGHEST + 1,
};

class LauncherTabbed : public wxNotebook
{
public:
	LauncherTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos,
		const wxSize &size, long style);
private:
};

class LauncherPanel : public wxPanel
{
public:
	LauncherPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos,
		const wxSize &size, long style);
private:
	LauncherTabbed *tabs;
};

#endif /* INCLUDED_LAUNCHER_PANEL_H */

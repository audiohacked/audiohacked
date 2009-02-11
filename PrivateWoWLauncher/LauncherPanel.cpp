#include "wx/wxprec.h"
 
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/app.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/textfile.h>
#include <wx/filefn.h>

#include "LauncherApp.h"
#include "LauncherFilefn.h"
#include "LauncherConfig.h"
#include "LauncherPanel.h"
#include "LauncherRealmlistPanel.h"

LauncherTabbed::LauncherTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos,
	const wxSize &size, long style) : wxNotebook(parent, id, pos, size, style)
{
	LauncherRealmlistPanel *Switcher = new LauncherRealmlistPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxNO_BORDER);
	AddPage(Switcher, wxString::FromAscii("RealmList Switcher"));
}

LauncherPanel::LauncherPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos,
	const wxSize &size, long style) : wxPanel(parent, id, pos, size, style)
{
	tabs = new LauncherTabbed(this, -1, wxDefaultPosition, wxDefaultSize, 0);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(tabs, 1, wxEXPAND|wxALL, 5);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}


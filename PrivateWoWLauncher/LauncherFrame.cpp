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
#include "LauncherConfig.h"
#include "LauncherFilefn.h"
#include "LauncherFrame.h"

BEGIN_EVENT_TABLE(LauncherFrame, wxFrame)
	EVT_BUTTON(BUTTON_PRIVATE, LauncherFrame::PrivateList)
	EVT_BUTTON(BUTTON_PRIVATE2, LauncherFrame::PrivateList2)
	EVT_BUTTON(BUTTON_BLIZZARD, LauncherFrame::BlizzardList)
	EVT_BUTTON(BUTTON_CUSTOM, LauncherFrame::CustomList)
	EVT_BUTTON(BUTTON_CACHE, LauncherFrame::ClearCache)
END_EVENT_TABLE()

LauncherFrame::LauncherFrame(
	const wxString& title, const wxPoint &pos, const wxSize &size)
	: wxFrame((wxFrame *) NULL, -1, title, pos, size)
{
	CreateStatusBar();
	SetStatusText(_T("2009 (C) Sean Nelson <snelson@nmt.edu>"));

/*
	LauncherTabbed *panel = new LauncherTabbed(this, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxNO_BORDER);
	panel->SetFocus();
*/
	myapp = &wxGetApp();
	wxPanel *panel = new wxPanel(this);
	PrivateRealmListButton = new wxButton(panel, BUTTON_PRIVATE, wxT("Use " PRIVATE_BUTTON_TEXT " Realmlist"));
	Private2RealmListButton = new wxButton(panel, BUTTON_PRIVATE2, wxT("Use " PRIVATE2_BUTTON_TEXT " Realmlist"));
	BlizzardRealmListButton = new wxButton(panel, BUTTON_BLIZZARD, wxT("Use Blizzard Realmlist"));
	CustomRealmListButton = new wxButton(panel, BUTTON_CUSTOM, wxT("Use Custom Realmlist:"));
	CustomRealmText = new wxTextCtrl(panel, TEXT_CUSTOM, wxEmptyString);
	ClearCacheButton = new wxButton(panel, BUTTON_CACHE, wxT("Clear WoW WDB Cache"));

	wxGridSizer *sizer = new wxGridSizer(3);
	sizer->Add(PrivateRealmListButton, 0, wxALL, 10);
	sizer->AddStretchSpacer();
	sizer->AddStretchSpacer();

	sizer->Add(Private2RealmListButton, 0, wxALL, 10);
	sizer->AddStretchSpacer();
	sizer->AddStretchSpacer();

	sizer->Add(BlizzardRealmListButton, 0, wxALL, 10);
	sizer->AddStretchSpacer();
	sizer->AddStretchSpacer();

	sizer->Add(CustomRealmListButton, 0, wxALL, 10);
	sizer->Add(CustomRealmText, 0, wxALL, 10);
	sizer->AddStretchSpacer();

	sizer->Add(ClearCacheButton, 0, wxALL, 10);
	sizer->AddStretchSpacer();
	sizer->AddStretchSpacer();

	panel->SetSizer(sizer);
	sizer->SetSizeHints(this);
}

LauncherFrame::~LauncherFrame()
{
}

void LauncherFrame::ClearCache(wxCommandEvent &event)
{
	wxString cachedir = wxString::FromAscii("Cache");
	//wxMessageBox(myapp->wow_path+cachedir);
	LauncherFilefn *cache = new LauncherFilefn();
	cache->DeleteCache(myapp->wow_path+cachedir);
}


void LauncherFrame::PrivateList(wxCommandEvent &event)
{
	//wxMessageBox(wxT("Using Private RealmList: ")+myapp->wow_path+wxT(" ")+wxT(PRIVATE_REALMLIST));
	wxString filestring = myapp->wow_path+wxT("/Data/enUS/realmlist.wtf");
	wxRemove(filestring);
	///*
	wxTextFile *file = new wxTextFile(filestring);
	file->Create();
	file->AddLine(wxString::FromAscii("set realmlist ")+wxT(PRIVATE_REALMLIST));
	file->AddLine(wxString::FromAscii("set patchlist ")+wxT(PRIVATE_PATCHLIST));
	file->AddLine(wxString::FromAscii("set realmlistbn \"\" "));
	file->AddLine(wxString::FromAscii("set portal us"));
	file->Write();
	file->Close();
	//*/
}

void LauncherFrame::PrivateList2(wxCommandEvent &event)
{
	//wxMessageBox(wxT("Using Private RealmList: ")+myapp->wow_path+wxT(" ")+wxT(PRIVATE2_REALMLIST));
	wxString filestring = myapp->wow_path+wxT("/Data/enUS/realmlist.wtf");
	wxRemove(filestring);
	wxTextFile *file = new wxTextFile(filestring);
	file->Create();
	file->AddLine(wxString::FromAscii("set realmlist ")+wxT(PRIVATE2_REALMLIST));
	file->AddLine(wxString::FromAscii("set patchlist ")+wxT(PRIVATE2_PATCHLIST));
	file->AddLine(wxString::FromAscii("set realmlistbn \"\" "));
	file->AddLine(wxString::FromAscii("set portal us"));
	file->Write();
	file->Close();
}

void LauncherFrame::CustomList(wxCommandEvent &event)
{
	//wxMessageBox(wxT("Using Private RealmList: ")+myapp->wow_path+wxT(" ")+wxT(PRIVATE2_REALMLIST));
	wxString filestring = myapp->wow_path+wxT("/Data/enUS/realmlist.wtf");
	if (CustomRealmText->GetValue().IsEmpty())
	{
		wxMessageBox(wxString::FromAscii("You did not input a valid Server string!"));
	}
	else
	{
		wxRemove(filestring);
		wxTextFile *file = new wxTextFile(filestring);
		file->Create();
		file->AddLine(wxString::FromAscii("set realmlist ")+CustomRealmText->GetValue());
		file->AddLine(wxString::FromAscii("set patchlist ")+wxT(BLIZZARD_PATCHLIST));
		file->AddLine(wxString::FromAscii("set realmlistbn \"\" "));
		file->AddLine(wxString::FromAscii("set portal us"));
		file->Write();
		file->Close();
	}
}

void LauncherFrame::BlizzardList(wxCommandEvent &event)
{
	//wxMessageBox(wxT("Using Blizzard's RealmList: ")+myapp->wow_path+wxT(" ")+wxT(BLIZZARD_REALMLIST));
	wxString filestring = myapp->wow_path+wxT("/Data/enUS/realmlist.wtf");
	wxRemove(filestring);
	wxTextFile *file = new wxTextFile(filestring);
	file->Create();
	file->AddLine(wxString::FromAscii("set realmlist ")+wxT(BLIZZARD_REALMLIST));
	file->AddLine(wxString::FromAscii("set patchlist ")+wxT(BLIZZARD_PATCHLIST));
	file->AddLine(wxString::FromAscii("set realmlistbn \"\" "));
	file->AddLine(wxString::FromAscii("set portal us"));
	file->Write();
	file->Close();
}

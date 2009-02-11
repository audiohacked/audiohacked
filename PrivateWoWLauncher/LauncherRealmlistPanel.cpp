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
#include "LauncherRealmlistPanel.h"

BEGIN_EVENT_TABLE(LauncherRealmlistPanel, wxPanel)
	EVT_BUTTON(BUTTON_PRIVATE, LauncherRealmlistPanel::PrivateList)
	EVT_BUTTON(BUTTON_PRIVATE2, LauncherRealmlistPanel::PrivateList2)
	EVT_BUTTON(BUTTON_BLIZZARD, LauncherRealmlistPanel::BlizzardList)
	EVT_BUTTON(BUTTON_CUSTOM, LauncherRealmlistPanel::CustomList)
	EVT_BUTTON(BUTTON_CACHE, LauncherRealmlistPanel::ClearCache)
END_EVENT_TABLE()

LauncherRealmlistPanel::LauncherRealmlistPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style)
	: wxPanel(parent)
{
	myapp = &wxGetApp();
	PrivateRealmListButton = new wxButton(this, BUTTON_PRIVATE, wxT("Use " PRIVATE_BUTTON_TEXT " Realmlist"));
	Private2RealmListButton = new wxButton(this, BUTTON_PRIVATE2, wxT("Use " PRIVATE2_BUTTON_TEXT " Realmlist"));
	BlizzardRealmListButton = new wxButton(this, BUTTON_BLIZZARD, wxT("Use Blizzard Realmlist"));
	CustomRealmListButton = new wxButton(this, BUTTON_CUSTOM, wxT("Use Custom Realmlist:"));
	CustomRealmText = new wxTextCtrl(this, TEXT_CUSTOM, wxEmptyString);
	ClearCacheButton = new wxButton(this, BUTTON_CACHE, wxT("Clear WoW WDB Cache"));


	/*
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
	*/
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(PrivateRealmListButton, 0, wxALL, 10);
	sizer->Add(Private2RealmListButton, 0, wxALL, 10);
	sizer->Add(BlizzardRealmListButton, 0, wxALL, 10);

	wxBoxSizer *custom_sizer = new wxBoxSizer(wxHORIZONTAL);
	custom_sizer->Add(CustomRealmListButton, 0, wxALL, 10);
	custom_sizer->Add(CustomRealmText, 0, wxALL, 10);
	sizer->Add(custom_sizer, 0, wxALL, 0);

	sizer->Add(ClearCacheButton, 0, wxALL, 10);
	sizer->AddSpacer(10);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

LauncherRealmlistPanel::~LauncherRealmlistPanel()
{
}

void LauncherRealmlistPanel::ClearCache(wxCommandEvent &event)
{
	wxString cachedir = wxString::FromAscii("Cache");
	//wxMessageBox(myapp->wow_path+cachedir);
	LauncherFilefn *cache = new LauncherFilefn();
	cache->DeleteCache(myapp->wow_path+cachedir);
}


void LauncherRealmlistPanel::PrivateList(wxCommandEvent &event)
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

void LauncherRealmlistPanel::PrivateList2(wxCommandEvent &event)
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

void LauncherRealmlistPanel::CustomList(wxCommandEvent &event)
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

void LauncherRealmlistPanel::BlizzardList(wxCommandEvent &event)
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

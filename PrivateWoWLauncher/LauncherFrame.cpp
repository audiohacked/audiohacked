#include "wx/wxprec.h"
 
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/app.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/textfile.h>

#include "LauncherApp.h"
#include "LauncherFrame.h"
#include "LauncherConfig.h"

BEGIN_EVENT_TABLE(LauncherFrame, wxFrame)
	EVT_BUTTON(BUTTON_PRIVATE, LauncherFrame::PrivateList)
	EVT_BUTTON(BUTTON_PRIVATE2, LauncherFrame::PrivateList2)
	EVT_BUTTON(BUTTON_BLIZZARD, LauncherFrame::BlizzardList)
END_EVENT_TABLE()

LauncherFrame::LauncherFrame(
	const wxChar *title)
	: wxFrame((wxFrame *) NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{
	myapp = &wxGetApp();
	wxButton *PrivateRealmList = new wxButton(this, BUTTON_PRIVATE, wxT("Use ")+wxT(PRIVATE_BUTTON_TEXT)+wxT(" Realmlist"));
	wxButton *Private2RealmList = new wxButton(this, BUTTON_PRIVATE2, wxT("Use ")+wxT(PRIVATE2_BUTTON_TEXT)+wxT(" Realmlist"));
	wxButton *BlizzardRealmList = new wxButton(this, BUTTON_BLIZZARD, wxT("Use Blizzard Realmlist"));

	wxBoxSizer *hsizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *vsizer = new wxBoxSizer(wxVERTICAL);
	vsizer->Add(PrivateRealmList, 0, wxALL, 10);
	vsizer->Add(BlizzardRealmList, 0, wxALL, 10);
	hsizer->Add(vsizer, 0, wxALL, 10);
	hsizer->AddStretchSpacer();
	SetSizer(hsizer);
	//hsizer->SetSizeHints(this);
}

LauncherFrame::~LauncherFrame()
{
}

void LauncherFrame::PrivateList(wxCommandEvent &event)
{
	//wxMessageBox(wxT("Using Private RealmList: ")+myapp->wow_path+wxT(" ")+wxT(PRIVATE_REALMLIST));
	wxString filestring = myapp->wow_path+wxT("/Data/enUS/realmlist.wtf");
	wxRemove(filestring);
	wxTextFile *file = new wxTextFile(filestring);
	file->Create();
	file->AddLine(wxString::FromAscii("set realmlist ")+wxT(PRIVATE_REALMLIST));
	file->AddLine(wxString::FromAscii("set patchlist ")+wxT(PRIVATE_PATCHLIST));
	file->AddLine(wxString::FromAscii("set realmlistbn \"\" "));
	file->AddLine(wxString::FromAscii("set portal us"));
	file->Write();
	file->Close();
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

#include "ChatCommon.h"
#include "ChatApp.h"
#include "ChatMessage.h"
#include "ChatWindow.h"
#include "ChatRosterData.h"
#include "ChatRoster.h"

BEGIN_EVENT_TABLE( ChatWindowRosterPanel, wxPanel )
	EVT_TREE_ITEM_ACTIVATED(WINDOW_RosterList, ChatWindowRosterPanel::NewChatWindow)
END_EVENT_TABLE()

ChatWindowRoster::ChatWindowRoster(Client *conn) :
wxFrame(NULL, -1, wxT("ChatRoster"), wxDefaultPosition, wxDefaultSize)
{
	j = conn;
	panel = new ChatWindowRosterPanel(this, -1, conn);
	panel->SetFocus();
}

ChatWindowRoster::~ChatWindowRoster()
{
	j->disconnect();
	delete j;
	panel->list->DeleteAllItems();
}

ChatWindowRosterPanel::ChatWindowRosterPanel(wxWindow *parent, wxWindowID id, Client *conn)
	: wxPanel(parent, id, wxDefaultPosition, wxDefaultSize)
{
	j = conn;
	list = new wxTreeCtrl(this, WINDOW_RosterList, wxDefaultPosition, wxDefaultSize,
	 	wxTR_FULL_ROW_HIGHLIGHT|wxTR_NO_LINES|wxTR_HIDE_ROOT|wxTR_SINGLE);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

	wxPanel *userPanel = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize);
	wxPanel *optionsPanel = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize);

	sizer->Add(userPanel, 0, wxALL, 10);
	sizer->Add(list, 1, wxALL|wxEXPAND, 10);
	sizer->Add(optionsPanel, 0, wxALL, 10);
	SetSizer(sizer);
	sizer->SetSizeHints(this);

	listRoot = list->AddRoot(_T("Roster"));
}

void ChatWindowRosterPanel::AddContact(wxString contact, JID jid)
{	
	ChatContactItemData *newContact = new ChatContactItemData(contact, jid);
	list->AppendItem(listRoot, contact, -1, -1, newContact);
}

void ChatWindowRosterPanel::NewChatWindow(wxTreeEvent &event)
{
	wxTreeItemId itemId = event.GetItem();
	ChatContactItemData *item = (ChatContactItemData *) list->GetItemData(itemId);
	//if (!item->hasWin) {
		//item->conn = j;
		//item->chatSess = new ChatMsgSess(j);
		//item->chatSess->m_session = item->chatSess->newSession( item->jid );
		//item->chatSess->m_session = item->chatSess->newSession( item->jid );
		//item->win = new ChatWindowChat(list, itemId);
		item->win->Show();
		//item->hasWin = true;
	//}
}

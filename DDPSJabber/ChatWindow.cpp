#include "ChatWindow.h"
#include "ChatMessage.h"

BEGIN_EVENT_TABLE( ChatWindowRosterPanel, wxPanel )
	EVT_TREE_ITEM_ACTIVATED(WINDOW_RosterList, ChatWindowRosterPanel::NewChatWindow)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE( ChatWindowChatPanel, wxPanel )
	EVT_BUTTON(BUTTON_SendMsg, ChatWindowChatPanel::SendMsg)
END_EVENT_TABLE()

ChatWindowRoster::ChatWindowRoster(Client *conn) :
wxFrame(NULL, -1, wxT("ChatRoster"), wxDefaultPosition, wxDefaultSize)
{
	j = conn;
	panel = new ChatWindowRosterPanel(this, -1, conn);
	panel->SetFocus();
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

void ChatWindowRosterPanel::AddContact(wxString contact, wxString jid)
{	
	if (contact == wxT("")) {
		contact = jid;
	}
	ChatContactItemData *newContact = new ChatContactItemData(contact, jid);
	list->AppendItem(listRoot, contact, -1, -1, newContact);
}

void ChatWindowRosterPanel::NewChatWindow(wxTreeEvent &event)
{
	wxTreeItemId itemId = event.GetItem();
	ChatContactItemData *item = (ChatContactItemData *)list->GetItemData(itemId);
	JID jid( wx2glooxString(item->GetJID()) );
	if (!item->HasWin()) {
		item->conn = j;
		item->sess = new ChatMsgSess(j);
		item->sess->m_session = item->sess->newSession( jid );
		ChatWindowChat *chat = new ChatWindowChat(list, item, itemId);
		chat->Show();
		item->SetHasWin(true);
	}
}

ChatWindowChat::ChatWindowChat(wxTreeCtrl *list, ChatContactItemData *data, wxTreeItemId id) :
wxFrame(NULL, -1, data->GetName(), wxDefaultPosition, wxDefaultSize)
{
	chat_contact_jid = data->GetJID();
	chat_contact_name = data->GetName();
	itemId = id;
	rosterList = list;
		
	panel = new ChatWindowChatPanel(this, -1, data, id);
	panel->SetFocus();
	
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(panel, 0, wxALL, 0);
	sizer->SetSizeHints(this);
}

ChatWindowChat::~ChatWindowChat()
{
	ChatContactItemData *item = (ChatContactItemData *)rosterList->GetItemData(itemId);
	item->SetHasWin(false);
}

ChatWindowChatPanel::ChatWindowChatPanel(wxWindow *parent, wxWindowID id, ChatContactItemData *data, wxTreeItemId treeId)
	: wxPanel(parent, id, wxDefaultPosition, wxDefaultSize)
{
	MsgSes = data->sess;
	chatText = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY);
	sendText = new wxTextCtrl(this, TEXT_MsgText, wxT(""), wxDefaultPosition, wxSize(200, 20));
	sendButton = new wxButton(this, BUTTON_SendMsg, wxT("Send"), wxDefaultPosition, wxDefaultSize);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(chatText, 1, wxEXPAND|wxTOP|wxLEFT|wxRIGHT, 10);

	wxFlexGridSizer *sendChat_sizer = new wxFlexGridSizer(2);
	sendChat_sizer->Add(sendText, 0, wxEXPAND);
	sendChat_sizer->Add(sendButton, 0, wxFIXED_MINSIZE|wxLEFT, 5);

	sizer->Add(sendChat_sizer, 0, wxALL|wxALIGN_RIGHT, 15);

	SetSizer(sizer);
	//sizer->SetSizeHints(this);
}

void ChatWindowChatPanel::SendMsg(wxCommandEvent &event)
{
	/*     
	sleep( 2 );
	m_session->send( re, sub );
	sleep( 2 );
	m_messageEventFilter->raiseMessageEvent( MessageEventDelivered );
	m_chatStateFilter->setChatState( ChatStateActive );
	*/
	wxTextCtrl* MsgText = (wxTextCtrl*) FindWindow(TEXT_MsgText);
	if (MsgText->GetValue() != wxT(""))
	{
		//MsgSes->m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
		//MsgSes->m_chatStateFilter->setChatState( ChatStateComposing );
		
		MsgSes->m_session->send(wx2glooxString(MsgText->GetValue()), "No Subject");
		
		//MsgSes->m_messageEventFilter->raiseMessageEvent( MessageEventDelivered );
		//MsgSes->m_chatStateFilter->setChatState( ChatStateActive );
		
		MsgText->SetValue(wxT(""));
	}
	//event.Skip();
}

#include "ChatCommon.h"
#include "ChatWindow.h"

BEGIN_EVENT_TABLE( ChatWindowChatPanel, wxPanel )
	EVT_BUTTON(BUTTON_SendMsg, ChatWindowChatPanel::SendMsg)
END_EVENT_TABLE()

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
	chatSes = data->chatSess;
	chatText = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY);
	sendText = new wxTextCtrl(this, TEXT_MsgText, wxT(""), wxDefaultPosition, wxSize(200, 20));
	sendButton = new wxButton(this, BUTTON_SendMsg, wxT("Send"), wxDefaultPosition, wxDefaultSize);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(chatText, 1, wxEXPAND|wxTOP|wxLEFT|wxRIGHT, 10);

	wxFlexGridSizer *sendChat_sizer = new wxFlexGridSizer(2);
	sendChat_sizer->Add(sendText, 0, wxEXPAND|wxRIGHT, 5);
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
		//chatSes->m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
		//chatSes->m_chatStateFilter->setChatState( ChatStateComposing );
		
		//chatSes->m_session->send(wx2glooxString(MsgText->GetValue()), "No Subject");
		wxLogMessage(MsgText->GetValue());
		
		//chatSes->m_messageEventFilter->raiseMessageEvent( MessageEventDelivered );
		//chatSes->m_chatStateFilter->setChatState( ChatStateActive );
		
		MsgText->SetValue(wxT(""));
	}
	//event.Skip();
}

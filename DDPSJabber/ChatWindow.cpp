#include "ChatCommon.h"
#include "ChatWindow.h"
#include "ChatRosterData.h"


BEGIN_EVENT_TABLE( ChatWindowChatPanel, wxPanel )
	EVT_BUTTON(BUTTON_SendMsg, ChatWindowChatPanel::SendMsg)
END_EVENT_TABLE()

ChatWindowChat::ChatWindowChat(wxTreeCtrl *list, wxTreeItemId id) :
wxFrame(NULL, -1, ((ChatContactItemData *)list->GetItemData(id))->name, wxDefaultPosition, wxDefaultSize)
{
	ChatContactItemData *data = (ChatContactItemData *)list->GetItemData(id);
	itemId = id;
	rosterList = list;
		
	panel = new ChatWindowChatPanel(this, -1, list, id);
	panel->SetFocus();
	
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(panel, 0, wxALL, 0);
	sizer->SetSizeHints(this);
}

ChatWindowChat::~ChatWindowChat()
{
	ChatContactItemData *item = (ChatContactItemData *)rosterList->GetItemData(itemId);
	item->hasWin = false;
}

ChatWindowChatPanel::ChatWindowChatPanel(wxWindow *parent, wxWindowID id, wxTreeCtrl *list, wxTreeItemId treeId)
	: wxPanel(parent, id, wxDefaultPosition, wxDefaultSize)
{
	contact_list = list;
	contact_id = treeId;
	
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
}

void ChatWindowChatPanel::SendMsg(wxCommandEvent &event)
{
	ChatContactItemData *data = (ChatContactItemData *)contact_list->GetItemData(contact_id);
	//wxTextCtrl* MsgText = (wxTextCtrl*) FindWindow(TEXT_MsgText);
	if (sendText->GetValue() != wxT(""))
	{
		//chatSes->m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
		//chatSes->m_chatStateFilter->setChatState( ChatStateComposing );

		wxLogMessage(sendText->GetValue());
		data->MsgSess->send(wx2glooxString(sendText->GetValue()), "No Subject");
		
		//chatSes->m_messageEventFilter->raiseMessageEvent( MessageEventDelivered );
		//chatSes->m_chatStateFilter->setChatState( ChatStateActive );
		
		sendText->SetValue(wxT(""));
	}
	//event.Skip();
}

#include "ChatCommon.h"
#include "ChatRosterData.h"
#include "ChatWindow.h"

BEGIN_EVENT_TABLE( ChatWindowChat, wxFrame )
	EVT_CLOSE(ChatWindowChat::OnCloseWindow)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE( ChatWindowChatPanel, wxPanel )
	EVT_BUTTON(BUTTON_SendMsg, ChatWindowChatPanel::SendMsg)
	EVT_TEXT_ENTER(TEXT_MsgText, ChatWindowChatPanel::SendMsg)
	EVT_TEXT(TEXT_MsgText, ChatWindowChatPanel::TextChanged)
END_EVENT_TABLE()

ChatWindowChat::ChatWindowChat(wxTreeCtrl *list, wxTreeItemId id) :
wxFrame(NULL, -1, ((ChatContactItemData *)list->GetItemData(id))->wx_jid, wxDefaultPosition, wxDefaultSize)
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
	
}

void ChatWindowChat::OnCloseWindow(wxCloseEvent& event)
{
	if (!event.CanVeto()) { // Test if we can veto this deletion
		this->Close();
		this->Destroy();// If not, destroy the window anyway.
	} else {
		event.Veto();// Notify the calling code that we didn't delete the frame.
		// user has closed the chat window
		//this->panel->chatSes->m_chatStateFilter->setChatState( ChatStateGone );
		//this->Hide();
		this->Show(FALSE);
	}
}


ChatWindowChatPanel::ChatWindowChatPanel(wxWindow *parent, wxWindowID id, wxTreeCtrl *list, wxTreeItemId treeId)
	: wxPanel(parent, id, wxDefaultPosition, wxDefaultSize)
{
	contact_list = list;
	contact_id = treeId;
	
	ChatContactItemData *data = (ChatContactItemData *)list->GetItemData(treeId);
	chatSes = data->chatSess;
	
	chatText = new wxTextCtrl(this, TEXT_ChatText, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY);
	sendText = new wxTextCtrl(this, TEXT_MsgText, wxT(""), wxDefaultPosition, wxSize(200, 20), wxTE_PROCESS_ENTER);
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
	wxTextCtrl* MsgText = (wxTextCtrl*) FindWindow(TEXT_MsgText);
	wxTextCtrl* ChatText = (wxTextCtrl*) FindWindow(TEXT_ChatText);
	if (MsgText->GetValue() != wxT(""))
	{
		wxLogMessage(MsgText->GetValue());
		chatSes->m_session->send(wx2glooxString(MsgText->GetValue()), "No Subject");
		ChatText->AppendText(wxT("me: ") + MsgText->GetValue() + wxT("\n"));
		MsgText->SetValue(wxT(""));
	}
	// acknowledge receiving of a message
	//chatSes->m_messageEventFilter->raiseMessageEvent( MessageEventDelivered );
}

void ChatWindowChatPanel::TextChanged(wxCommandEvent &event)
{
	// user is typing a message
	//chatSes->m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
}
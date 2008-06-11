#include "ChatCommon.h"
#include "ChatApp.h"
#include "ChatRosterData.h"
#include "ChatRoster.h"
#include "ChatWindow.h"

void ChatRoster::onResourceBindError( ResourceBindError error )
{
//	printf( "onResourceBindError: %d\n", error );
}

void ChatRoster::onSessionCreateError( SessionCreateError error )
{
//	printf( "onSessionCreateError: %d\n", error );
}

void ChatRoster::handleItemSubscribed( const JID& jid )
{
//	printf( "subscribed %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemAdded( const JID& jid )
{
//	printf( "added %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemUnsubscribed( const JID& jid )
{
//	printf( "unsubscribed %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemRemoved( const JID& jid )
{
//	printf( "removed %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemUpdated( const JID& jid )
{
//	printf( "updated %s\n", jid.bare().c_str() );
}

void ChatRoster::handleRoster( const Roster& roster )
{
	Roster::const_iterator it = roster.begin();
	for( ; it != roster.end(); ++it )
	{	
		ChatApp &myApp = ::wxGetApp();
		wxString contact((*it).second->jid().c_str(), wxConvUTF8);
		wxString name((*it).second->name().c_str(), wxConvUTF8);
		
		myApp.win->panel->AddContact( name, contact );
	}
}

void ChatRoster::handleRosterError( Stanza *stanza )
{
	//printf( "a roster-related error occured\n" );
}

void ChatRoster::handleRosterPresence( const RosterItem& item, const std::string& resource,
                          Presence presence, const std::string& /*msg*/ )
{
	//printf( "presence received: %s/%s -- %d\n", item.jid().c_str(), resource.c_str(), presence );
}

void ChatRoster::handleSelfPresence( const RosterItem& item, const std::string& resource,
                          Presence presence, const std::string& /*msg*/ )
{
	//printf( "self presence received: %s/%s -- %d\n", item.jid().c_str(), resource.c_str(), presence );
}

bool ChatRoster::handleSubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
{
	//printf( "subscription: %s\n", jid.bare().c_str() );
	StringList groups;
	JID id( jid );
	j->rosterManager()->subscribe( id, "", groups, "" );
	return true;
}

bool ChatRoster::handleUnsubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
{
	//printf( "unsubscription: %s\n", jid.bare().c_str() );
	return true;
}

void ChatRoster::handleNonrosterPresence( Stanza *stanza )
{
	//printf( "received presence from entity not in the roster: %s\n", presence.from().full().c_str() );
}

void ChatRoster::handleLog( LogLevel level, LogArea area, const std::string& message )
{
	//printf("log: level: %d, area: %d, %s\n", level, area, message.c_str() );
}


ChatContactItemData::ChatContactItemData(wxString contact, wxString jid)
{
	contact_jid = jid;
	contact_name = contact;
	hasWin = false;
}

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
		//item->sess = new ChatMsgSess(j);
		//item->sess->m_session = item->sess->newSession( jid );
		ChatWindowChat *chat = new ChatWindowChat(list, item, itemId);
		chat->Show();
		item->SetHasWin(true);
	}
}

#include "ChatCommon.h"
#include "ChatApp.h"
#include "ChatMessage.h"
#include "ChatWindow.h"
#include "ChatRosterData.h"
#include "ChatRoster.h"

BEGIN_EVENT_TABLE( ChatWindowRosterPanel, wxPanel )
	EVT_TREE_ITEM_ACTIVATED(WINDOW_RosterList, ChatWindowRosterPanel::NewChatWindow)
END_EVENT_TABLE()

void ChatRoster::onResourceBindError( ResourceBindError error )
{
	printf( "onResourceBindError: %d\n", error );
}

void ChatRoster::onSessionCreateError( SessionCreateError error )
{
	printf( "onSessionCreateError: %d\n", error );
}

void ChatRoster::handleItemSubscribed( const JID& jid )
{
	printf( "subscribed %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemAdded( const JID& jid )
{
	printf( "added %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemUnsubscribed( const JID& jid )
{
	printf( "unsubscribed %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemRemoved( const JID& jid )
{
	printf( "removed %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemUpdated( const JID& jid )
{
	printf( "updated %s\n", jid.bare().c_str() );
}

void ChatRoster::handleRoster( const Roster& roster )
{
	ChatApp &myApp = ::wxGetApp();
	Roster::const_iterator it = roster.begin();
	for( ; it != roster.end(); ++it )
	{	
		wxString contact = gloox2wxString((*it).second->name());
		wxString itemName;
		wxLogMessage (contact);
		if (contact == wxT(""))
		{
			JID roster_jid((*it).second->jid());
			itemName = gloox2wxString(roster_jid.username());
		}
		else
		{
			itemName = contact;
		}
		
		wxLogMessage( wxT("add contact jid: ") + gloox2wxString((*it).second->jid()) );
				
		ChatContactItemData *newContact = new ChatContactItemData(contact, (*it).second->jid());
		newContact->conn = myApp.thread->server->FetchConnection();
		
		wxTreeItemId id = myApp.win->panel->list->AppendItem(myApp.win->panel->listRoot, itemName, -1, -1, newContact);
		newContact->itemId = id;

		newContact->chatSess = new ChatMsgSess(myApp.thread->server->FetchConnection());
		newContact->chatSess->m_session = newContact->chatSess->newSession( (*it).second->jid() );

		newContact->win = new ChatWindowChat(myApp.win->panel->list, id);
		newContact->hasWin = true;
	}
}

void ChatRoster::handleRosterError( Stanza *stanza )
{
	printf( "a roster-related error occured\n" );
}

void ChatRoster::handleRosterPresence( const RosterItem& item, const std::string& resource,
                          Presence presence, const std::string& /*msg*/ )
{
	printf( "presence received: %s/%s -- %d\n", item.jid().c_str(), resource.c_str(), presence );
}

void ChatRoster::handleSelfPresence( const RosterItem& item, const std::string& resource,
                          Presence presence, const std::string& /*msg*/ )
{
	printf( "self presence received: %s/%s -- %d\n", item.jid().c_str(), resource.c_str(), presence );
}

bool ChatRoster::handleSubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
{
	wxLogMessage(wxT("subscription: ") + gloox2wxString(jid.bare()));
	StringList groups;
	JID id( jid );
	j->rosterManager()->subscribe( id, "", groups, "" );
	return true;
}

bool ChatRoster::handleUnsubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
{
	wxLogMessage(wxT("unsubscription: ") + gloox2wxString(jid.bare()));
	return true;
}

void ChatRoster::handleNonrosterPresence( Stanza *stanza )
{
	printf( "received presence from entity not in the roster: %s\n", stanza->from().full().c_str() );
	//StringList groups;
	//j->rosterManager()->subscribe( stanza->from(), "", groups, "" );
}

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

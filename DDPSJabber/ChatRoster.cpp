#include "ChatCommon.h"
#include "ChatApp.h"
#include "ChatRoster.h"

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
	//printf( "roster arriving\nitems:\n" );
	Roster::const_iterator it = roster.begin();
	for( ; it != roster.end(); ++it )
	{	
		ChatApp &myApp = ::wxGetApp();
		wxString contact((*it).second->jid().c_str(), wxConvUTF8);
		wxString name((*it).second->name().c_str(), wxConvUTF8);
		
		myApp.win->panel->AddContact( name, contact );
		//wxLogMessage(wxT("new contact to list: ") + contact);
		/*printf( "jid: %s, name: %s, subscription: %d\n",
		   (*it).second->jid().c_str(), (*it).second->name().c_str(),
		   (*it).second->subscription() );
		StringList g = (*it).second->groups();
		StringList::const_iterator it_g = g.begin();
		for( ; it_g != g.end(); ++it_g )
		printf( "\tgroup: %s\n", (*it_g).c_str() );
		RosterItem::ResourceMap::const_iterator rit = (*it).second->resources().begin();
		for( ; rit != (*it).second->resources().end(); ++rit )
		printf( "resource: %s\n", (*rit).first.c_str() );*/
	}
}

void ChatRoster::handleRosterError( const IQ& /*iq*/ )
{
	//printf( "a roster-related error occured\n" );
}

void ChatRoster::handleRosterPresence( const RosterItem& item, const std::string& resource,
                          Presence::PresenceType presence, const std::string& /*msg*/ )
{
	//printf( "presence received: %s/%s -- %d\n", item.jid().c_str(), resource.c_str(), presence );
}

void ChatRoster::handleSelfPresence( const RosterItem& item, const std::string& resource,
                          Presence::PresenceType presence, const std::string& /*msg*/ )
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

void ChatRoster::handleNonrosterPresence( const Presence& presence )
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

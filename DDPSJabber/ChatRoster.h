#include <gloox/client.h>
#include <gloox/rostermanager.h>
using namespace gloox;

#include <stdio.h>
#include <locale.h>
#include <string>

class ChatRoster : public RosterListener
{
  public:
	ChatRoster(Client *client)
	{
		j = client;
		client->rosterManager()->registerRosterListener( this );
	}
    virtual ~ChatRoster(){}

	virtual void onResourceBindError( ResourceBindError error );
	virtual void onSessionCreateError( SessionCreateError error );
	virtual void handleItemSubscribed( const JID& jid );
	virtual void handleItemAdded( const JID& jid );
	virtual void handleItemUnsubscribed( const JID& jid );
	virtual void handleItemRemoved( const JID& jid );
	virtual void handleItemUpdated( const JID& jid );
	virtual void handleRoster( const Roster& roster );
	virtual void handleRosterError( const IQ& iq );
	virtual void handleRosterPresence( const RosterItem& item, 
		const std::string& resource, Presence::PresenceType presence,
		const std::string& msg );

    virtual void handleSelfPresence( const RosterItem& item, 
		const std::string& resource, Presence::PresenceType presence,
		const std::string& msg );
		
	virtual bool handleSubscriptionRequest( const JID& jid, const std::string& msg );
	virtual bool handleUnsubscriptionRequest( const JID& jid, const std::string& msg );
	virtual void handleNonrosterPresence( const Presence& presence );
	virtual void handleLog( LogLevel level, LogArea area, const std::string& message );

  private:
    Client *j;
};

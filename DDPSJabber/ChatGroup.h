#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/mucroomhandler.h>
#include <gloox/mucroom.h>
#include <gloox/disco.h>
#include <gloox/presence.h>
#include <gloox/message.h>
#include <gloox/dataform.h>
#include <gloox/gloox.h>
#include <gloox/lastactivity.h>
#include <gloox/loghandler.h>
#include <gloox/logsink.h>
using namespace gloox;

#include <stdio.h>
#include <locale.h>
#include <string>

#ifdef WIN32
#include <windows.h>
#endif

class ChatGroup : public MUCRoomHandler
{
  public:
    ChatGroup() {}

	/*void start()
    {
      JID jid( "hurkhurk@example.net/gloox" );
      j = new Client( jid, "hurkhurks" );
      j->registerConnectionListener( this );
      j->setPresence( Presence::Available, -1 );
      j->disco()->setVersion( "gloox muc_example", GLOOX_VERSION, "Linux" );
      j->disco()->setIdentity( "client", "bot" );
      j->setCompression( false );
      StringList ca;
      ca.push_back( "/path/to/cacert.crt" );
      j->setCACerts( ca );

      j->logInstance().registerLogHandler( LogLevelDebug, LogAreaAll, this );

      JID nick( "test@conference.jabber.org/glooxmuctest" );
      m_room = new MUCRoom( j, nick, this, 0 );

      if( j->connect( false ) )
      {
        ConnectionError ce = ConnNoError;
        while( ce == ConnNoError )
        {
          ce = j->recv();
        }
        printf( "ce: %d\n", ce );
      }

      // cleanup
      delete m_room;
      delete j;
    }

    virtual void onConnect()
    {
      printf( "connected!!!\n" );
      m_room->join();
      m_room->getRoomInfo();
      m_room->getRoomItems();
    }*/

    virtual void handleMUCParticipantPresence( MUCRoom * /*room*/, 
		const MUCRoomParticipant participant, Presence::PresenceType presence );
	virtual void handleMUCMessage( MUCRoom* /*room*/, const Message& msg, bool priv );
	virtual void handleMUCSubject( MUCRoom * /*room*/, const std::string& nick,
	 	const std::string& subject );
	virtual void handleMUCError( MUCRoom * /*room*/, StanzaError error );
    virtual void handleMUCInfo( MUCRoom * /*room*/, int features, const std::string& name,
		const DataForm* infoForm );
	virtual void handleMUCItems( MUCRoom * /*room*/, const Disco::ItemList& items );
	virtual void handleMUCInviteDecline( MUCRoom * /*room*/, const JID& invitee, 
		const std::string& reason );
	virtual bool handleMUCRoomCreation( MUCRoom *room );

  private:
    Client *j;
    MUCRoom *m_room;
};
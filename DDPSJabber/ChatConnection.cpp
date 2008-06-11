#include "ChatCommon.h"
#include "ChatConnection.h"

ChatConnThread::ChatConnThread() : wxThread()
{
	Create();
	server = new ChatConn();
	threadConn = server->FetchConnection();
}

void *ChatConnThread::Entry()
{
	server->FetchConnection()->connect( true );
}

/*void ChatConnThread::OnExit(){}*/

ChatConn::ChatConn()
{
	JID jid( "ddps@localhost/DDPSChat" );
	//jid.setServer("192.168.1.204");

	//wxLogMessage( wxT("server -- ") + wxString(jid.server().c_str(), wxConvUTF8) );
	//wxLogMessage( wxT("RAWserver -- ") + wxString(jid.serverRaw().c_str(), wxConvUTF8) );
	//wxLogMessage( wxT("username -- ") + wxString(jid.username().c_str(), wxConvUTF8) );
	//wxLogMessage( wxT("resource -- ") + wxString(jid.resource().c_str(), wxConvUTF8) );

	conn = new Client(jid, "letmein");

	conn->setSASLMechanisms(SaslMechPlain);

	conn->registerConnectionListener( this );
	conn->registerPresenceHandler( this );

	conn->disco()->setVersion( "ddps", "client", "test" );
	conn->disco()->setIdentity( "client", "bot" );
	conn->disco()->addFeature( XMLNS_CHAT_STATES );
	
	conn->setPresence( Presence::Available, 1 );
	
}

void ChatConn::onConnect()
{
	//wxLogMessage(wxT("connection"));
}

void ChatConn::onDisconnect(ConnectionError e)
{
	//wxLogMessage(wxT("disconnection"));    
}

bool ChatConn::onTLSConnect(const CertInfo& info)
{
	//wxLogMessage(wxT("TLS Connection"));
    return true;
}

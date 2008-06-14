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

void ChatConnThread::OnExit()
{
	//server->FetchConnection()->rosterManager()->removeRosterListener();
	//delete rosterListener;

	//server->FetchConnection()->disposeMessageSession(server->FetchConnection()->cMsg->m_session);
	//delete cMsg

	//server->FetchConnection()->disconnect();
}

ChatConn::ChatConn()
{
	JID jid( "ddps@localhost/DDPSChat" );

	conn = new Client(jid, "letmein");

	conn->setSASLMechanisms(SaslMechPlain);

	conn->registerConnectionListener( this );
	conn->registerPresenceHandler( this );

	conn->disco()->setVersion( "ddps", "client", "test" );
	conn->disco()->setIdentity( "client", "bot" );
	conn->disco()->addFeature( XMLNS_CHAT_STATES );
	
	conn->setPresence( PresenceAvailable, 1 );
	
}

void ChatConn::onConnect()
{
	wxLogMessage(wxT("connection"));
}

void ChatConn::onDisconnect(ConnectionError e)
{
	wxLogMessage(wxT("disconnection"));    
}

bool ChatConn::onTLSConnect(const CertInfo& info)
{
	wxLogMessage(wxT("TLS Connection"));
    return true;
}

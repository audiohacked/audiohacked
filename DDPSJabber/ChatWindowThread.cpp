#include "ChatWindowThread.h"

ChatWindowThread::ChatWindowThread() : wxThread()
{
	Create();
	server = new ChatConn();
	threadConn = server->FetchConnection();
}

void *ChatWindowThread::Entry()
{
	server->FetchConnection()->connect( true );
}

void ChatWindowThread::OnExit()
{
	//server->FetchConnection()->rosterManager()->removeRosterListener();
	//delete rosterListener;

	//server->FetchConnection()->disposeMessageSession(server->FetchConnection()->cMsg->m_session);
	//delete cMsg

	//server->FetchConnection()->disconnect();
}

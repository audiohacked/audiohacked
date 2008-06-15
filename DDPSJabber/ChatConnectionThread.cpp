#include "ChatConnectionThread.h"

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

#include "ChatApp.h"

IMPLEMENT_APP(ChatApp)

bool ChatApp::OnInit()
{
	FILE *myLogFile = fopen("log.txt", "a+");
	wxLogStderr *LogFile = new wxLogStderr(myLogFile);
	wxLog::SetActiveTarget(LogFile);
	
	thread = new ChatConnThread();
	InitChat();
	thread->Run();
	
	win = new ChatWindowRoster(thread->server->FetchConnection());
	win->Show(TRUE);
	SetTopWindow(win);

	return TRUE;
}

/*int ChatApp::OnExit()
{
	server->FetchConnection()->disconnect();

	delete win;

	server->FetchConnection()->rosterManager()->removeRosterListener();
	delete rosterListener;

	server->FetchConnection()->disposeMessageSession(cMsg->m_session);
	//delete cMsg

	server->FetchConnection()->disconnect();
	delete server;

	thread->Delete();
	delete thread;

	wxApp::CleanUp();	
}*/

void ChatApp::InitChat()
{
	rosterListener = new ChatRoster( thread->server->FetchConnection() );
	cMsg = new ChatMsgSess( thread->server->FetchConnection() );
	//cAccount = new ChatAccount( thread->server->FetchConnection() );
}
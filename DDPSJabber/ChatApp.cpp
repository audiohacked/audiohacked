#include "ChatApp.h"

IMPLEMENT_APP(ChatApp)

bool ChatApp::OnInit()
{
	FILE *myLogFile = fopen("log.txt", "a+");
	wxLogStderr *LogFile = new wxLogStderr(myLogFile);
	wxLog::SetActiveTarget(LogFile);
	
	//thread = new ChatConnThread();
	server = new ChatConn();
	InitChat();
	//thread->Run();
	
	win = new ChatWindowRoster(server->FetchConnection());
	win->Show(TRUE);
	SetTopWindow(win);

	server->FetchConnection()->connect(true);
	return TRUE;
}

int ChatApp::OnExit()
{
/*
	if (win->IsShown())
	{
		win->Destroy();
	}
*/

	server->FetchConnection()->rosterManager()->removeRosterListener();
	delete rosterListener;

	//thread->server->FetchConnection()->disposeMessageSession(cMsg->m_session);
	//delete cMsg;

	//thread->server->FetchConnection()->disconnect();

	//delete thread->server;
	//delete server;

	//thread->Delete();
	//delete thread;

	wxApp::CleanUp();	
}

void ChatApp::InitChat()
{
	rosterListener = new ChatRoster( server->FetchConnection() );
	cMsg = new ChatMsgSess( server->FetchConnection() );
	//cAccount = new ChatAccount( thread->server->FetchConnection() );
}
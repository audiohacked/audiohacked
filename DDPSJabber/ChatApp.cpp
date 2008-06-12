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

void ChatApp::InitChat()
{
	rosterListener = new ChatRoster( thread->server->FetchConnection() );
	cMsg = new ChatMsgSess( thread->server->FetchConnection() );
	//cAccount = new ChatAccount( thread->server->FetchConnection() );
}
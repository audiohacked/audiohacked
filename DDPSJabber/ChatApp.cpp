#include "ChatApp.h"

IMPLEMENT_APP(ChatApp)

bool ChatApp::OnInit()
{
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
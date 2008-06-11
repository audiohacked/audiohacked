#include "ChatApp.h"
#include "ChatMessage.h"
#include "ChatRoster.h"

#include <stdlib.h>

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
	ChatMsgSess *cMsg = new ChatMsgSess( thread->server->FetchConnection() );

	ChatRoster *rosterListener = new ChatRoster( thread->server->FetchConnection() );

	//ChatAccount *cAccount = new ChatAccount( thread->server->FetchConnection() );
}
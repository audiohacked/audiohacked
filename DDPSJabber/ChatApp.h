#ifndef __CHAT_APP_H
#define __CHAT_APP_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include "ChatConnection.h"
	#include "ChatRoster.h"
	#include "ChatMessage.h"

	class ChatApp : public wxApp
	{
		public:
			virtual bool OnInit();
			virtual int OnExit();
			void InitChat();
			ChatConnThread *thread;
			ChatConn *server;
			ChatWindowRoster *win;
			ChatRoster *rosterListener;
			ChatMsgSess *cMsg;
			//ChatAccount *cAccount;
	};

	DECLARE_APP(ChatApp)

#endif

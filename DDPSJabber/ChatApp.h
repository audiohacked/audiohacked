#ifndef __CHAT_APP_H
#define __CHAT_APP_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include "ChatConnection.h"
	#include "ChatWindow.h"

	class ChatApp : public wxApp
	{
		public:
			virtual bool OnInit();
			void InitChat();
			ChatConnThread *thread;
			ChatConn *server;
			ChatWindowRoster *win;
	};

	DECLARE_APP(ChatApp)

#endif

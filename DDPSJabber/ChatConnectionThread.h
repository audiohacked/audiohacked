#ifndef __CHAT_CONNECTION_THREAD_H
#define __CHAT_CONNECTION_THREAD_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include "ChatConnection.h"

	class ChatConnThread : public wxThread
	{
		public:
			ChatConnThread();
			virtual void *Entry();
			virtual void OnExit();
			ChatConn *server;
						
		private:
			Client *threadConn;
	};

#endif

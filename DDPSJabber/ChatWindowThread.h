#ifndef __CHAT_WINDOW_THREAD_H
#define __CHAT_WINDOW_THREAD_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	class ChatWindowThread : public wxThread
	{
		public:
			ChatWindowThread();
			virtual void *Entry();
			virtual void OnExit();
			ChatConn *server;
						
		private:
			Client *threadConn;
	};

#endif

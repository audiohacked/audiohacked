#ifndef __CHAT_CONNECTION_H
#define __CHAT_CONNECTION_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	//#include "ChatCommon.h"

	#include <gloox/client.h>
	
	#include <gloox/presencehandler.h>
	#include <gloox/presence.h>
	
	#include <gloox/connectionlistener.h>
	#include <gloox/connectiontcpclient.h>
	#include <gloox/disco.h>
	#include <gloox/gloox.h>
	using namespace gloox;

	class ChatConn : public ConnectionListener, PresenceHandler
	{
		public:
			ChatConn();
			virtual void onConnect();
			virtual void onDisconnect( ConnectionError e );
			virtual bool onTLSConnect( const CertInfo& info );
			virtual void handlePresence( const Presence& presence )
			{
				conn->setPresence( Presence::Available, 1 );
			}
			
			Client *FetchConnection(){ return conn; }
			
		private:
			Client *conn;
	};

	class ChatConnThread : public wxThread
	{
		public:
			ChatConnThread();
			virtual void *Entry();
			//virtual void OnExit();
			ChatConn *server;
						
		private:
			Client *threadConn;
	};

#endif

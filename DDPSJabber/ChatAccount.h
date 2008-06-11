#ifndef __CHAT_ACCOUNT_H
#define __CHAT_ACCOUNT_H

	#include <gloox/presencehandler.h>
	#include <gloox/presence.h>
	#include <gloox/lastactivity.h>

	#include <gloox/client.h>
	#include <gloox/connectionlistener.h>
	#include <gloox/registration.h>

	#include <gloox/gloox.h>
	using namespace gloox;

	class ChatAccount : public  PresenceHandler
	{
		public:
			ChatAccount(Client *client)
			{
				j = client;
				client->registerPresenceHandler( this );
			}
			virtual void handlePresence( const Presence& presence );

		private:
			Client *j;
	};

#endif

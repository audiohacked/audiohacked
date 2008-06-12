#ifndef __CHAT_MESSAGE_H
#define __CHAT_MESSAGE_H

	#include <gloox/client.h>
	#include <gloox/messagehandler.h>
	#include <gloox/messagesessionhandler.h>
	#include <gloox/messageeventhandler.h>
	#include <gloox/messageeventfilter.h>
	#include <gloox/chatstatehandler.h>
	#include <gloox/chatstatefilter.h>
	#include <gloox/gloox.h>
	using namespace gloox;

	class ChatMsgSess : public MessageSessionHandler, MessageEventHandler,
	 							ChatStateHandler, MessageHandler
	{
		public:
			ChatMsgSess(Client *conn);
			virtual void handleMessageSession( MessageSession *msgSes );
			virtual void handleMessage( Stanza *stanza, MessageSession *msgSes );
			virtual void handleMessageEvent(const JID &jid, MessageEventType MsgEvent);
			virtual void handleChatState( const JID &jid, ChatStateType ChatState);
			MessageSession *m_session;
			MessageEventFilter *m_messageEventFilter;
			ChatStateFilter *m_chatStateFilter;
			Client *m_client;

			MessageSession* ChatMsgSess::newSession( const JID& to )
			{
				MessageSession* session = new MessageSession( m_client, to );
				session->registerMessageHandler( this );
				return session;
			}
		
	};

#endif

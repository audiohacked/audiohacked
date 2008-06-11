#ifndef __CHAT_MESSAGE_H
#define __CHAT_MESSAGE_H

	#include <gloox/client.h>
	#include <gloox/message.h>
	#include <gloox/messagehandler.h>
	#include <gloox/messagesessionhandler.h>
	#include <gloox/messageeventhandler.h>
	#include <gloox/messageeventfilter.h>
	#include <gloox/chatstatehandler.h>
	#include <gloox/chatstatefilter.h>
	#include <gloox/gloox.h>
	using namespace gloox;

class ChatMsgSess : public MessageSessionHandler, MessageEventHandler, ChatStateHandler, MessageHandler
{
	public:
		ChatMsgSess(Client *conn);
		MessageSession* ChatMsgSess::newSession( const JID& to );
		virtual void handleMessageSession( MessageSession *msgSes );
		//virtual void handleMessage( const Message &msg );
		virtual void handleMessage( const Message &msg, MessageSession *msgSes );
		virtual void handleMessageEvent(const JID &jid, MessageEventType MsgEvent);
		virtual void handleChatState( const JID &jid, ChatStateType ChatState);
		MessageSession *m_session;
		MessageEventFilter *m_messageEventFilter;
		ChatStateFilter *m_chatStateFilter;

	private:
		Client *m_client;
		
};

#endif

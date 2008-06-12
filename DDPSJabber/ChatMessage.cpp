#include "ChatCommon.h"
#include "ChatMessage.h"
/**
new incoming chat:
	loop through wxTreeCtrl to see if one exsits
new outgoing chat:
	loop through wxTreeCtrl to see if one exsits
on app close:
	loop through wxTreeCtrl and close windows and sessions; clean up

// user is typing a message
m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
// acknowledge receiving of a message
m_messageEventFilter->raiseMessageEvent( MessageEventDelivered );
// user is not actively paying attention to the chat
m_chatStateFilter->setChatState( ChatStateInactive );
// user has closed the chat window
m_chatStateFilter->setChatState( ChatStateGone );
*/

ChatMsgSess::ChatMsgSess(Client *conn) {
	m_client = conn;
	conn->registerMessageSessionHandler( this, 0 );
}

void ChatMsgSess::handleMessageSession( MessageSession *msgSes )
{
/*
	check for new chat: loop thru list
	if new chat: create new window and session
*/

/*
	printf( "got new session\n");
	// this example can handle only one session. so we get rid of the old session
*/
	m_client->disposeMessageSession( m_session );
	m_session = msgSes;
	m_session->registerMessageHandler( this );
	m_messageEventFilter = new MessageEventFilter( m_session );
	m_messageEventFilter->registerMessageEventHandler( this );
	m_chatStateFilter = new ChatStateFilter( m_session );
	m_chatStateFilter->registerChatStateHandler( this );
}

void ChatMsgSess::handleMessage( Stanza *stanza, MessageSession *msgSes )
{
	wxString who = gloox2wxString(stanza->from().full());
	wxString text = gloox2wxString(stanza->body());
//	wxLogMessage(  wxT("msg from: ")+who+wxT(" body: ")+text  );
}

void ChatMsgSess::handleMessageEvent(const JID &jid, MessageEventType MsgEvent)
{
	/*display contact's Message Event*/
}

void ChatMsgSess::handleChatState( const JID &jid, ChatStateType ChatState)
{
	/*display contact's Chat State*/
}

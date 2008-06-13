#ifndef __CHAT_ROSTER_H
#define __CHAT_ROSTER_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/treectrl.h>

	#include <gloox/client.h>
	#include <gloox/rostermanager.h>
	#include <gloox/gloox.h>
	using namespace gloox;

	#include <stdio.h>
	#include <locale.h>
	#include <string>

	class ChatRoster : public RosterListener
	{
	  public:
		ChatRoster(Client *client)
		{
			j = client;
			client->rosterManager()->registerRosterListener( this );
		}
	    virtual ~ChatRoster(){}

		virtual void onResourceBindError( ResourceBindError error );
		virtual void onSessionCreateError( SessionCreateError error );
		virtual void handleItemSubscribed( const JID& jid );
		virtual void handleItemAdded( const JID& jid );
		virtual void handleItemUnsubscribed( const JID& jid );
		virtual void handleItemRemoved( const JID& jid );
		virtual void handleItemUpdated( const JID& jid );
		virtual void handleRoster( const Roster& roster );
		virtual void handleRosterError(  Stanza *stanza  );
		virtual void handleRosterPresence( const RosterItem& item, 
			const std::string& resource, Presence presence,
			const std::string& msg );

	    virtual void handleSelfPresence( const RosterItem& item, 
			const std::string& resource, Presence presence,
			const std::string& msg );
		
		virtual bool handleSubscriptionRequest( const JID& jid, const std::string& msg );
		virtual bool handleUnsubscriptionRequest( const JID& jid, const std::string& msg );
		virtual void handleNonrosterPresence( Stanza *stanza );

	  private:
	    Client *j;
	};

	class ChatWindowRosterPanel : public wxPanel
	{
		public:
			ChatWindowRosterPanel(wxWindow *parent, wxWindowID id, Client *conn);
			void AddContact(wxString contact, JID jid);
			void NewChatWindow(wxTreeEvent &event);
			wxTreeCtrl *list;
			wxTreeItemId listRoot;
			Client *j;
		DECLARE_EVENT_TABLE()
	};

	class ChatWindowRoster : public wxFrame
	{
		public:
			ChatWindowRoster(Client *conn);
			virtual ~ChatWindowRoster();
			ChatWindowRosterPanel *panel;
		private:
			Client *j;
	};

#endif
#ifndef __CHAT_WINDOW_H
#define __CHAT_WINDOW_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
		
	#include <gloox/client.h>
	#include <gloox/gloox.h>
	using namespace gloox;

	#include "ChatCommon.h"

	class ChatWindowRosterPanel : public wxPanel
	{
		public:
			ChatWindowRosterPanel(wxWindow *parent, wxWindowID id, Client *conn);
			void AddContact(wxString contact, wxString jid);
			void NewChatWindow(wxTreeEvent &event);
		private:
			wxTreeCtrl *list;
			wxTreeItemId listRoot;
			Client *j;
		DECLARE_EVENT_TABLE()
	};
	
	class ChatWindowRoster : public wxFrame
	{
		public:
			ChatWindowRoster(Client *conn);
			virtual ~ChatWindowRoster(){ j->disconnect(); delete j; }
			ChatWindowRosterPanel *panel;
		private:
			Client *j;
	};
	
	class ChatWindowChatPanel : public wxPanel
	{
		public:
			ChatWindowChatPanel(wxWindow *parent, wxWindowID id, ChatContactItemData *data, wxTreeItemId itemId);
			void SendMsg(wxCommandEvent &event);
			ChatMsgSess *MsgSes;
			//MessageSession *MsgSes;
		private:
			wxTextCtrl *chatText;
			wxTextCtrl *sendText;
			wxButton *sendButton;
		DECLARE_EVENT_TABLE()
	};
	
	class ChatWindowChat : public wxFrame
	{
		public:
			ChatWindowChat(wxTreeCtrl *list, ChatContactItemData *data, wxTreeItemId id);
			virtual ~ChatWindowChat();
			ChatWindowChatPanel *panel;
		private:
			wxTreeItemId itemId;
			wxTreeCtrl *rosterList;
			wxString chat_contact_jid, chat_contact_name;
	};
	
/*	
	class ChatWindowGroupChat : public wxFrame
	{
		public:
			ChatWindowGroupChat(){}
			
	};
*/
#endif
	
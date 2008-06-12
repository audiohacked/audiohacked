#ifndef __CHAT_WINDOW_H
#define __CHAT_WINDOW_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/treectrl.h>
		
	#include <gloox/client.h>
	#include <gloox/gloox.h>
	using namespace gloox;
		
	class ChatWindowChatPanel : public wxPanel
	{
		public:
			ChatWindowChatPanel(wxWindow *parent, wxWindowID id, wxTreeCtrl *list, wxTreeItemId itemId);
			void SendMsg(wxCommandEvent &event);
		private:
			wxTreeCtrl *contact_list;
			wxTreeItemId contact_id;
			wxTextCtrl *chatText;
			wxTextCtrl *sendText;
			wxButton *sendButton;
		DECLARE_EVENT_TABLE()
	};
	
	class ChatWindowChat : public wxFrame
	{
		public:
			ChatWindowChat(wxTreeCtrl *list, wxTreeItemId id);
			virtual ~ChatWindowChat();
			ChatWindowChatPanel *panel;
		private:
			wxTreeItemId itemId;
			wxTreeCtrl *rosterList;
	};
	
/*	
	class ChatWindowGroupChat : public wxFrame
	{
		public:
			ChatWindowGroupChat(){}
			
	};
*/
#endif
	
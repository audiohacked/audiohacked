#ifndef __CHAT_COMMON_H
#define __CHAT_COMMON_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/treectrl.h>
	#include <string>
	
	#include "ChatMessage.h"

	//wxString LoginUsername = wxT("audiohacked");
	//wxString LoginPassword = wxT("deathball");

	enum
	{
		WINDOW_RosterList,
		TEXT_MsgText,
		BUTTON_SendMsg
	};

	std::string wx2glooxString( wxString str);
	wxString gloox2wxString( std::string str);

	class ChatContactItemData : public wxTreeItemData
	{
		public:
			ChatContactItemData(wxString contact, wxString contact_jid);
			const wxString GetName() const { return contact_name; }
		    const wxString GetJID() const { return contact_jid; }
			const bool HasWin() const { return hasWin; }
			void SetHasWin(bool has) { hasWin = has; }
			ChatMsgSess *sess;
			//MessageSession *sess;
			Client *conn;

		private:
			wxString contact_jid;
			wxString contact_name;
			bool hasWin;
	};

#endif

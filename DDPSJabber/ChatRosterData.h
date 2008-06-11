#ifndef __CHAT_ROSTER_DATA_H
#define __CHAT_ROSTER_DATA_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include "ChatMessage.h"

	class ChatContactItemData : public wxTreeItemData
	{
		public:
			ChatContactItemData(wxString contact, wxString contact_jid);
			const wxString GetName() const { return contact_name; }
		    const wxString GetJID() const { return contact_jid; }
			const bool HasWin() const { return hasWin; }
			void SetHasWin(bool has) { hasWin = has; }
			ChatMsgSess *chatSess;
			MessageSession *MsgSess;
			Client *conn;
			wxString contact_jid;
			wxString contact_name;
			bool hasWin;
	};

#endif

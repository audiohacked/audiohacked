#ifndef __CHAT_ROSTER_DATA_H
#define __CHAT_ROSTER_DATA_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include "ChatMessage.h"
	#include "ChatWindow.h"

	class ChatContactItemData : public wxTreeItemData
	{
		public:
			ChatContactItemData(wxString contact, JID contact_jid);
			Client *conn;
			ChatMsgSess *chatSess;
			MessageSession *MsgSess;
			JID jid;
			wxString name;
			ChatWindowChat *win;
			bool hasWin;
	};

#endif

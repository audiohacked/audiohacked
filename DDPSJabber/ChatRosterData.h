#ifndef __CHAT_ROSTER_DATA_H
#define __CHAT_ROSTER_DATA_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/treectrl.h>

	#include "ChatMessage.h"
	#include "ChatWindow.h"

	class ChatContactItemData : public wxTreeItemData
	{
		public:
			ChatContactItemData(wxString contact, JID contact_jid);
			virtual ~ChatContactItemData();

			bool hasWin;
			wxTreeItemId itemId;

			Client *conn;
			ChatMsgSess *chatSess;

			JID jid;
			wxString name;
			wxString wx_jid;

			ChatWindowChat *win;
	};

#endif

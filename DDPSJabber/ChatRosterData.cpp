#include "ChatRosterData.h"

ChatContactItemData::ChatContactItemData(wxString contact, JID contact_jid)
{
	jid = contact_jid;
	wx_jid = wxString(contact_jid.full().c_str(), wxConvUTF8);
	name = contact;
	hasWin = false;
	conn = NULL;
	win = NULL;
	
/*
//	item->conn = j;
	item->win = new ChatWindowChat(list, itemId);
	item->win->Show();
	item->hasWin = true;
*/	
}

ChatContactItemData::~ChatContactItemData()
{
	//delete win;
	hasWin = false;

	//delete jid;
	//delete name;

	//delete chatSess;
	//delete MsgSess;

	//delete conn;
}
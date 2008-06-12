#include "ChatRosterData.h"

ChatContactItemData::ChatContactItemData(wxString contact, JID jid)
{
	jid = jid;
	name = contact;
	hasWin = false;
	conn = NULL;
	chatSess = NULL;
	MsgSess = NULL;
	win = NULL;
}

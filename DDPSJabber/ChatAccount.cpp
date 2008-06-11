#include "ChatCommon.h"
#include "ChatAccount.h"

void ChatAccount::handlePresence( const Presence& presence )
{
	this.setPresence( Presence::Available );
}

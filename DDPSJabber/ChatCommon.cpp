#include "ChatCommon.h"
#include "ChatRosterData.h"

std::string wx2glooxString( wxString str )
{
	return std::string(str.mb_str());
}

wxString gloox2wxString( std::string str )
{
	return wxString(str.c_str(), wxConvUTF8);
}

wxTreeItemId findTreeItem(wxTreeCtrl* pTreeCtrl, const wxTreeItemId& root, const wxString& text)
{
	wxTreeItemId item=root;
	wxString findtext(text);

	wxLogMessage(wxT("findTreeItem: ") + findtext);
	ChatContactItemData *itemdata = (ChatContactItemData *)pTreeCtrl->GetItemData(item);
	wxLogMessage(itemdata->wx_jid);
	wxString itemtext = wxString(itemdata->wx_jid);
	//if (itemtext.Contains(findtext)) return item;
	if (itemtext == findtext) return item;
	else return findTreeItem(pTreeCtrl, pTreeCtrl->GetNextSibling(item), text);
	return item;
}

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
	wxTreeItemId item=root, child;
	wxTreeItemIdValue cookie;
	ChatContactItemData *itemdata;
	wxString findtext(text), itemtext;
	bool bFound;

	wxLogMessage(wxT("findTreeItem: ") + text);

	while(item.IsOk())
	{
		itemdata = (ChatContactItemData *)pTreeCtrl->GetItemData(item);
		itemtext = gloox2wxString(itemdata->jid.full());
		wxLogMessage(wxT("findTreeItem: ") + itemtext);
		if(itemtext == findtext) return item;
		item = pTreeCtrl->GetNextSibling(item);
	} // while(item.IsOk())

	return item;
}

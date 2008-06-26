#include "wxbencode.hpp"

void wx_entry_print(entry e, int depth)
{
	wxString padding(wxT(""));
	switch(e.type())
	{
		case entry::int_t:
			wxLogMessage(wxT("print:")+padding.Pad(depth, '\t')+wxString::Format(_T("int: %u"), e.integer()));
			break;

		case entry::string_t:
			wxLogMessage(wxT("print:")+padding.Pad(depth, '\t')+wxString::Format(wxT("str-len: %u "), e.string().length())+wxT("str: ")+wxString(e.string().c_str(), wxConvUTF8));
			break;

		case entry::list_t:
			for (entry::list_type::const_iterator i = e.list().begin(); i != e.list().end(); ++i)
			{
				wx_entry_print(*i, depth+1);
			}
			break;

		case entry::dictionary_t:
			for (entry::dictionary_type::const_iterator i = e.dict().begin(); i != e.dict().end(); ++i)
			{
				wx_entry_print(i->first, depth+1);// write key
				wx_entry_print(i->second, depth+1);// write value
			}
			break;

		default:
			break;
	}
}

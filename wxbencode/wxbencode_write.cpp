#include "wxbencode.hpp"

void wx_bencode(wxTextOutputStream &out, entry e)
{
	switch(e.type())
	{
		case entry::int_t:
			out.WriteString(wxT("i"));
			out.WriteString(wxString::Format(_T("%u"), e.integer()));
			out.WriteString(wxT("e"));
			break;

		case entry::string_t:
			out.WriteString(wxString::Format(_T("%u"), e.string().length()));
			out.WriteString(wxT(":"));
			out.WriteString(wxString(e.string().c_str(), wxConvUTF8));
			break;

		case entry::list_t:
			out.WriteString(wxT("l"));
			for (entry::list_type::const_iterator i = e.list().begin(); i != e.list().end(); ++i)
			{
				wx_bencode(out, *i);
			}
			out.WriteString(wxT("e"));
			break;

		case entry::dictionary_t:
			out.WriteString(wxT("d"));
			for (entry::dictionary_type::const_iterator i = e.dict().begin(); i != e.dict().end(); ++i)
			{
				out.WriteString(wxString::Format(_T("%u"), i->first.length()));
				out.WriteString(wxT(":"));
				out.WriteString(wxString(i->first.c_str(), wxConvUTF8));
				
				wx_bencode(out, i->second);
			}
			out.WriteString(wxT("e"));
			break;

		default:
			break;
	}
}

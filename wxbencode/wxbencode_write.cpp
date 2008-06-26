#include "wxbencode.hpp"

void wx_bencode(wxDataOutputStream &out_data, wxTextOutputStream &out_text, entry e)
{
	switch(e.type())
	{
		case entry::int_t:
			out_data.Write8('i');
			out_text.WriteString( wxString::Format(wxT("%u"), e.integer()) );
			out_data.Write8('e');
			break;

		case entry::string_t:
			out_text.WriteString( wxString::Format(wxT("%u"), e.string().length()) );
			out_data.Write8(':');
			for (int i=0; i<e.string().length(); ++i)
			{
				out_data.Write8( e.string().at(i) );
			}
			break;

		case entry::list_t:
			out_data.Write8('l');
			for (entry::list_type::const_iterator i = e.list().begin(); i != e.list().end(); ++i)
			{
				wx_bencode(out_data, out_text, *i);
			}
			out_data.Write8('e');
			break;

		case entry::dictionary_t:
			out_data.Write8('d');
			for (entry::dictionary_type::const_iterator i = e.dict().begin(); i != e.dict().end(); ++i)
			{
				out_text.WriteString( wxString::Format(wxT("%u"), i->first.length()) );
				out_data.Write8(':');
				for (int j=0; j < i->first.length(); ++j)
				{
					out_data.Write8( i->first.at(j) );
				}
				wx_bencode(out_data, out_text, i->second);
			}
			out_data.Write8('e');
			break;

		default:
			break;
	}
}

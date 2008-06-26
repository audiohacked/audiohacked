#include "wxbencode.hpp"

std::string read_until(wxFileInputStream &file, wxDataInputStream &data, char stop);
void read_string(wxFileInputStream &file, wxDataInputStream &data, int len, std::string &ret);

int wx_bdecode(wxFileInputStream &file, wxDataInputStream &data, entry &ret, int depth)
{
	char myByte;
	wxString padding(wxT(""));
	if (depth >= 100)
	{
		return 0;
	}
	if (file.Eof())
	{
		return 0;
	}
	switch(file.Peek())
	{
		case 'i':
			{
				if (file.Peek() == 'i') data.Read8();
				ret = entry(entry::int_t);
				std::string val = read_until(file, data, 'e');
				ret.integer() = boost::lexical_cast<entry::integer_type>(val);
				if (file.Peek() == 'e') data.Read8();
				wxLogMessage(wxT("num: ")+wxString(val.c_str(), wxConvUTF8));
			}
			break;

		case 'l':
			{
				if (file.Peek() == 'l') data.Read8();
				ret = entry(entry::list_t);
				while (file.Peek() != 'e')
				{
					ret.list().push_back(entry());
					entry& list = ret.list().back();
					wx_bdecode(file, data, list, depth + 1);
				}
				if (file.Peek() == 'e') data.Read8();
			}
			break;

		case 'd':
			{
				if (file.Peek() == 'd') data.Read8();
				ret = entry(entry::dictionary_t);
				while (file.Peek() != 'e')
				{
					entry key;
					wx_bdecode(file, data, key, depth + 1);
					if (key.type() != entry::string_t)
					{
						return 0;
					}

					entry dict;
					wx_bdecode(file, data, dict, depth + 1);
					ret.dict().insert(std::pair<std::string, entry>(key.string(), dict));
				}
				if (file.Peek() == 'e')  data.Read8();
			}
			break;

		default:
			if(isdigit(file.Peek()))
			{
				ret = entry(entry::string_t);
				std::string len_s = read_until(file, data, ':');
				if (file.Peek() == ':') data.Read8();
				int len = std::atoi(len_s.c_str());
				read_string(file, data, len, ret.string());
			}
			else
			{
				return 0;
			}
			break;
	}// switch
}

std::string read_until(wxFileInputStream &file, wxDataInputStream &data, char stop)
{
	std::string ret;
	if (file.Eof()) return ret;
	while (file.Peek() != stop)
	{
		ret += file.Peek();
		data.Read8();
		if (file.Eof()) return ret;
	}
	return ret;
}

void read_string(wxFileInputStream &file, wxDataInputStream &data, int len, std::string &ret)
{
	for (int i = 0; i < len; ++i)
	{
		if (file.Eof()) return;
		ret += file.Peek();
		data.Read8();
	}
}

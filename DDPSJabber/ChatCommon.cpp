#include "ChatCommon.h"

std::string wx2glooxString( wxString str )
{
	return std::string(str.mb_str());
}

wxString gloox2wxString( std::string str )
{
	return wxString(str.c_str(), wxConvUTF8);
}
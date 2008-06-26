#include "wxbencode.hpp"

#include <stdio.h>

IMPLEMENT_APP(wxbencode_test)

int wxbencode_test::OnRun()
{

	wxFileInputStream input_file(wxT("original.torrent"));
	wxFileOutputStream output_file(wxT("test_binary.torrent"));
	wxDataInputStream input_data(input_file);
	wxDataOutputStream output_data(output_file);
	wxTextOutputStream output_text(output_file);

	wxLogMessage(wxT("decoding torrent file"));
	wx_bdecode(input_file, input_data, e, 0);
	wxLogMessage(wxT("done decoding"));

	//wx_entry_print(e,0);

	wxLogMessage(wxT("encoding torrent file"));
	wx_bencode(output_data, output_text, e);
	wxLogMessage(wxT("done encoding"));

	return 0;
}

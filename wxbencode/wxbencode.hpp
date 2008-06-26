#ifndef __WX_BENCODE_TEST_H
#define __WX_BENCODE_TEST_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/datstrm.h>
	#include <wx/txtstrm.h>
	#include <wx/wfstream.h>
	
	#include <boost/lexical_cast.hpp>
	//#include <boost/static_assert.hpp>
	
	#include <libtorrent/config.hpp>
	#include <libtorrent/entry.hpp>
	
	using namespace libtorrent;

	int wx_bdecode(wxFileInputStream &file, wxDataInputStream &data, entry &ret, int depth);
	void wx_bencode(wxTextOutputStream &out, entry e);
	void wx_entry_print(entry e, int depth);

	class wxbencode_test : public wxAppConsole
	{
		public:
			virtual int OnRun();
			entry e;
	};
	
	DECLARE_APP(wxbencode_test)
	
#endif
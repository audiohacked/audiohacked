PROJECT( wxbencode )

FIND_PACKAGE( wxWidgets )
SET(SRCS
	wxbencode.cpp
	wxbencode_print.cpp
	wxbencode_read.cpp
	wxbencode_write.cpp
	)
SUBDIRS( libtorrent )

IF(wxWidgets_FOUND)
	INCLUDE (${wxWidgets_USE_FILE})
	INCLUDE_DIRECTORIES(
		${wxWidgets_INCLUDE_DIRS} 
		libtorrent/include
		libtorrent/include/libtorrent
		/opt/local/include
		)
	LINK_DIRECTORIES(
		/opt/local/lib
		)
	ADD_EXECUTABLE(wxbencode ${SRCS})
	TARGET_LINK_LIBRARIES(wxbencode torrent ${wxWidgets_LIBRARIES})
ENDIF(wxWidgets_FOUND)
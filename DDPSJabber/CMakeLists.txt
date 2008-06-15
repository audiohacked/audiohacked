PROJECT(ChatApp)

### Begin Source Files
SET(SRCS
	ChatCommon.cpp
	ChatApp.cpp
	ChatConnection.cpp
	ChatConnectionThread.cpp
	ChatMessage.cpp
	ChatRoster.cpp
	#ChatGroup.cpp
	ChatWindow.cpp
	ChatRosterData.cpp
)
SET(HDRS
	ChatCommon.h
	ChatApp.h
	ChatConnection.h
	ChatConnectionThread.h
	ChatMessage.h
	ChatRoster.h
	#ChatGroup.h
	ChatWindow.h
	ChatRosterData.h
)
### End Source Files

### Mac OS X Executable Stuff
SET(GUI_TYPE MACOSX_BUNDLE)
### End Mac OS X Executable Stuff

### Search for wxWidgets
FIND_PACKAGE(wxWidgets)

INCLUDE(
	${wxWidgets_USE_FILE}
)

INCLUDE_DIRECTORIES(
	${INCLUDE_DIRECTORIES}
	${CMAKE_SOURCE_DIR}
	${CMAKE_BINARY_DIR}
	${wxWidgets_INCLUDE_DIRS}
)
### End Search for wxWidgets

#### Search for Gloox (jabber library)
INCLUDE( ${CMAKE_ROOT}/Modules/UsePkgConfig.cmake )
PKGCONFIG(gloox GLOOX_INCLUDE_DIR GLOOX_LINK_DIR GLOOX_LINK_FLAGS GLOOX_CFLAGS)
INCLUDE_DIRECTORIES(
	${INCLUDE_DIRECTORIES}
	${GLOOX_INCLUDE_DIR}
)
LINK_DIRECTORIES(
	${GLOOX_LINK_DIR}
)
### End Search for Gloox

SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${GLOOX_LINK_FLAGS})

### Define Executable
ADD_EXECUTABLE(DDPSChat ${GUI_TYPE} ${SRCS} ${HDRS})
TARGET_LINK_LIBRARIES(DDPSChat ${wxWidgets_LIBRARIES})
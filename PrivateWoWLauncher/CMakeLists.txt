PROJECT(PrivateWoWLauncher)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(SRCS
	LauncherApp.cpp
	LauncherFrame.cpp
)
SET(PRIVATE_BUTTON_TEXT "Audiohacked"
	CACHE STRING "Set the Text for Private Realm Button")
SET(PRIVATE_REALMLIST 129.138.36.134 
	CACHE STRING "Set the URL for Your Private Realmlist")
SET(PRIVATE_PATCHLIST us.version.worldofwarcraft.com 
	CACHE STRING "Set the URL for Your Private Patchlist")

SET(PRIVATE2_BUTTON_TEXT "Laladan"
	CACHE STRING "Set the Text for Your Private2 Realm Button")
SET(PRIVATE2_REALMLIST 129.138.36.111 
	CACHE STRING "Set the URL for Your Private2 Realmlist")
SET(PRIVATE2_PATCHLIST us.version.worldofwarcraft.com
	CACHE STRING "Set the URL for Your Private2 Patchlist")

SET(BLIZZARD_REALMLIST us.logon.worldofwarcraft.com
	CACHE STRING "Set the URL for Blizzard's Realmlist")
SET(BLIZZARD_PATCHLIST us.version.worldofwarcraft.com
	CACHE STRING "Set the URL for Blizzard's Patchlist")

CONFIGURE_FILE(
	${CMAKE_SOURCE_DIR}/LauncherConfig.h.in
	${CMAKE_BINARY_DIR}/LauncherConfig.h
	ESCAPE_QUOTES
)

FIND_PACKAGE(wxWidgets COMPONENTS base core net)

IF(wxWidgets_FOUND)
	INCLUDE_DIRECTORIES(
		${CMAKE_SOURCE_DIR}
		${CMAKE_BINARY_DIR}
	)

	IF(WIN32)
		SET(GUI WIN32)
	ELSE(WIN32)
		IF(APPLE)
			SET(GUI MACOSX_BUNDLE)
		ENDIF(APPLE)
	ENDIF(WIN32)

	INCLUDE(${wxWidgets_USE_FILE})
	ADD_EXECUTABLE(PrivateWoWLauncher ${GUI} ${SRCS})
	TARGET_LINK_LIBRARIES(PrivateWoWLauncher ${wxWidgets_LIBRARIES})

ENDIF(wxWidgets_FOUND)


#include <FTGL/ftgl.h>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>

#include "text.hpp"
#include "settings.hpp"

FTGL::FTGLfont *font = NULL;

void init_font(void)
{
	/* Create a pixmap font from a TrueType file. */
	font = FTGL::ftglCreatePixmapFont("/Library/Fonts/Arial Unicode.ttf");
}

void cleanup_font(void)
{
	/* Destroy the font object. */
	FTGL::ftglDestroyFont(font);
}

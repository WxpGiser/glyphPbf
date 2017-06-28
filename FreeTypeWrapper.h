#pragma once

// freetype2
extern "C"
{
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
}


class FreeTypeWrapper
{
public:
	FreeTypeWrapper();
	~FreeTypeWrapper();

	FT_Face getFace(std::string textFont);
protected:
	FT_Library _library;

	typedef std::map<std::string, FT_Face> FT_FaceMap;
	FT_FaceMap _ft_faceMap;
};


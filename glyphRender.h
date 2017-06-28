#pragma once

#include "FreeTypeWrapper.h"

namespace sdf_glyph_foundry
{
	struct glyph_info;
}

class GlyphRender
{
public:
	GlyphRender(std::string& textFont);
	~GlyphRender();

	sdf_glyph_foundry::glyph_info* renderSDFGlyph(uint32_t code_point);

protected:
	std::string _textFont;

	FreeTypeWrapper* _freeTypeWrapper;
	FT_Face _ft_face;
	float _glyphSize;
};
#include "stdafx.h"
#include "glyphRender.h"


#include "glyph_foundry/mapbox/glyph_foundry.hpp"
#include "glyph_foundry/mapbox/glyph_foundry_impl.hpp"



GlyphRender::GlyphRender(std::string& textFont)
{
	_textFont = textFont;
	_freeTypeWrapper = new FreeTypeWrapper();
	_ft_face = _freeTypeWrapper->getFace(textFont);

	_glyphSize = 24.0;
	FT_Set_Char_Size(_ft_face, 0, (FT_F26Dot6)(_glyphSize * (1 << 6)), 0, 0);
}

GlyphRender::~GlyphRender()
{	
}

sdf_glyph_foundry::glyph_info* GlyphRender::renderSDFGlyph(uint32_t code_point)
{

	// Set character sizes.
	//double size = 24.0;
	//FT_Set_Char_Size(_ft_face, 0, (FT_F26Dot6)(size * (1 << 6)), 0, 0);

	// Get FreeType face from face_ptr.
	FT_UInt char_index = FT_Get_Char_Index(_ft_face, code_point);

	if (!char_index) {
		//fprintf(stderr, "could not find a glyph for this code point\n");
		return nullptr;
	}

	sdf_glyph_foundry::glyph_info* glyph = new sdf_glyph_foundry::glyph_info;
	glyph->glyph_index = char_index;
	sdf_glyph_foundry::RenderSDF(*glyph, _glyphSize, 3, 0.25, _ft_face);


	return glyph;
}
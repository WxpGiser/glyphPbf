#ifndef SDF_GLYPH_INFO_HPP
#define SDF_GLYPH_INFO_HPP

#include <string>
#include <stdint.h>

namespace sdf_glyph_foundry
{

	struct glyph_info
	{
		glyph_info()
		: glyph_index(0),
		bitmap(""),
		char_index(0),
		left(0),
		top(0),
		width(0),
		height(0),
		advance(0.0),
		line_height(0.0),
		ascender(0.0),
		descender(0.0) {}
		unsigned glyph_index;
		std::string bitmap;
		// Position in the string of all characters i.e. before itemizing
		unsigned char_index;
		int32_t left;
		int32_t top;
		uint32_t width;
		uint32_t height;
		double advance;
		// Line height returned by FreeType, includes normal font
		// line spacing, but not additional user defined spacing
		double line_height;
		// Ascender and descender from baseline returned by FreeType
		double ascender;
		double descender;
	};

} // ns sdf_glyph_foundry

#endif // SDF_GLYPH_INFO_HPP
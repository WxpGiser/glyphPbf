#include "stdafx.h"
#include "FreeTypeWrapper.h"


FreeTypeWrapper::FreeTypeWrapper()
{
	_library = nullptr;
	FT_Error error = FT_Init_FreeType(&_library);
	if (error) {
		fprintf(stderr, "could not open FreeType library");
	}
}


FreeTypeWrapper::~FreeTypeWrapper()
{
	FT_FaceMap::iterator iter = _ft_faceMap.begin();
	while (iter != _ft_faceMap.end())
	{
		FT_Face ft_face = iter->second;
		if (ft_face)
		{
			FT_Done_Face(ft_face);
			ft_face = nullptr;
		}

		++iter;
	}
	
	if (_library)
	{
		FT_Done_FreeType(_library);
		_library = nullptr;
	}
}

FT_Face FreeTypeWrapper::getFace(std::string textFont)
{
	FT_FaceMap::iterator iter = _ft_faceMap.find(textFont);
	if (iter == _ft_faceMap.end())
	{
		FT_Face ft_face = nullptr;
		FT_Error face_error = FT_New_Face(_library, textFont.c_str(), 0, &ft_face);//"D:/sdf-glyph-foundry-master/test/fonts/arial unicode ms.ttf"
		if (face_error) {
			fprintf(stderr, "could not open font");
			return nullptr;
		}
		
		_ft_faceMap.insert(make_pair(textFont, ft_face));

		return ft_face;
	}

	return iter->second;
}
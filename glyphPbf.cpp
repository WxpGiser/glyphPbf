// glyphPbf.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "glyphs.pb.h"
#include "glyphRender.h"
#include "glyph_foundry/mapbox/glyph_info.hpp"

#include <fstream>
#include <direct.h>

int _tmain(int argc, _TCHAR* argv[])
{
	string outdir;
	string fontfile;

	string temp = string((char*)argv[0], strlen((char*)argv[0]));
	int pos = temp.find_last_of('.');
	string sub = temp.substr(0, pos+1);
	sub += "cfg";
	std::ifstream in(sub, std::ios::in);

	while (!in.eof())
	{
		string line;
		getline(in, line);
		pos = line.find('=');
		string sub = line.substr(0, pos);
		if (sub == string("outputdir"))
		{
			outdir = line.substr(pos + 1, line.length());
		}
		else if (sub == string("fontfile"))
		{
			fontfile = line.substr(pos + 1, line.length());
		}
	}
	//string outdir = "e:/fonts/";

	_mkdir(outdir.c_str());

	//string fontfile = "D:/sdf-glyph-foundry-master/test/fonts/arial unicode ms.ttf";
	GlyphRender render(fontfile);

	vector<uint32_t> fails;

	uint32_t id = 0;
	for (int i = 0; i < 256; ++i)
	{
		char bs[33];
		sprintf_s(bs, "%d-%d", i * 256, i * 256 + 255);

		llmr::glyphs::glyphs *glyphs = new llmr::glyphs::glyphs();

		llmr::glyphs::fontstack *fontstack = glyphs->add_stacks();
		fontstack->set_name("Arial Unicode MS");
		fontstack->set_range(bs);

		for (int k = 0; k < 256; ++k)
		{
			uint32_t code_point = id++;
			sdf_glyph_foundry::glyph_info* info = render.renderSDFGlyph(code_point);
			if (info)
			{
				llmr::glyphs::glyph *glyph = fontstack->add_glyphs();
				glyph->set_id(code_point);
				glyph->set_bitmap(info->bitmap);
				glyph->set_width(info->width);
				glyph->set_height(info->height);
				glyph->set_left(info->left);
				glyph->set_top(info->top - 24);
				glyph->set_advance(info->advance);
				delete info;
			}
			else
			{
				fails.push_back(code_point);
			}
		}

		int32_t len = glyphs->ByteSize();
		char* pdata = new char[len];
		glyphs->SerializeToArray(pdata, len);

		string file = outdir + string(bs) + string(".pbf");
		std::ofstream out(file, std::ios::binary);

		out.write(pdata, len);

		out.close();
	}

	printf("失败个数:%d\n", fails.size());

	return 0;
}


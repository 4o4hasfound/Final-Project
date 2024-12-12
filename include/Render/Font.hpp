#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <allegro5/allegro_font.h>

#include "Debug/Log.hpp"

class Font {
	friend class Text;
public:
	Font();
	Font(const std::string& file);
	~Font();

	void load(const std::string& file);
private:
	std::string m_fontfile;
	std::unordered_map<int, ALLEGRO_FONT*> m_fonts;

	ALLEGRO_FONT* getFont(int size);
};
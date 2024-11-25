#pragma once
#include <iostream>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap_io.h>

#include "Debug/Log.hpp"

#include "Math/Vector.hpp"

class Texture {
public:
	Texture();
	Texture(const vec2& size);
	Texture(const std::string& filename);
	~Texture();

	const vec2& getSize() const;
	ALLEGRO_BITMAP* getBitmap() const;
private:
	void load(const std::string& filename);

	vec2 m_size;
	ALLEGRO_BITMAP* m_texture;
};
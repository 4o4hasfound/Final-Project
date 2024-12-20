#pragma once
#include <iostream>
#include <unordered_map>

#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap_io.h>

#include "Debug/Log.hpp"

#include "Math/Vector.hpp"

class Texture {
	friend class Engine;
public:
	Texture();
	// Empty texture
	Texture(const vec2& size);

	Texture(ALLEGRO_BITMAP* data);

	// Read the texture from a file
	Texture(const std::string& filename);

	// The destructor will destroy the bitmap
	~Texture();

	// The copy constructor will clone the bitmap
	Texture(const Texture& texture);
	// The move constructor will not clone the bitmap
	Texture(Texture&& texture);
	// The assign operator will clone the bitmap
	void operator=(const Texture& texture);

	// Load the texture from a file
	void load(const std::string& filename);

	const vec2& size() const;
	ALLEGRO_BITMAP* getBitmap() const;

	bool empty() const;
private:
	vec2 m_size;
	ALLEGRO_BITMAP* m_texture;

	static std::unordered_map<std::string, ALLEGRO_BITMAP*> s_textureMap;
	
	static void cleanup();
};
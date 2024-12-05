#pragma once
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#include "Math/Vector.hpp"

#include "Render/Texture.hpp"
#include "Render/Drawable.hpp"
#include "Render/RenderWindow.hpp"

#include "Math/Vector.hpp"

// If the outlineThickness is not 0, then the rectangle will not be filled
// If the texture is not null, then the rectangnle will use the texture
class Rectangle : public Drawable {
public:
	Rectangle(const vec2& _size = vec2(0));
	
	virtual void draw(const Texture* texture = nullptr) override;

	vec2 size = vec2(0);
	vec2 position = vec2(0);
	vec4 color = vec4(0, 0, 0, 255);
	float rotation = 0.0f;

	bool useRotationCenter = false;
	vec2 rotationCenter = vec2(0);

	float outlineThickness = 0.0f;
	vec4 outlineColor = vec4(0, 0, 0, 255);

	bvec2 flip = bvec2(0);
protected:
	virtual void draw(const RenderWindow* window, const Texture* texture = nullptr) override;
};

// If the outlineThickness is not 0, then the circle will not be filled
class Circle : public Drawable {
public:
	Circle(float _radius = 0.0f);

	virtual void draw(const Texture* texture = nullptr) override;

	float radius = 0.0f;
	vec2 position = vec2(0);
	vec4 color = vec4(0, 0, 0, 255);

	float outlineThickness = 0.0f;
	vec4 outlineColor = vec4(0, 0, 0, 255);
protected:
	virtual void draw(const RenderWindow* window, const Texture* texture = nullptr) override;
};

class Line : public Drawable {
public:
	Line();
	Line(const vec2 _start, const vec2 _end, float _thickness = 1.0);

	virtual void draw(const Texture* texture = nullptr) override;

	vec2 start = vec2(0);
	vec2 end = vec2(0);
	float thickness = 1.0f;
	vec2 position = vec2(0);
	vec4 color = vec4(0, 0, 0, 255);
protected:
	virtual void draw(const RenderWindow* window, const Texture* texture = nullptr) override;
};
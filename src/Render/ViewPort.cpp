#include "Render/ViewPort.hpp"

ViewPort::ViewPort()
	: position(0.0f), size(0.0f) {
}

ViewPort::ViewPort(const vec2& pos, const vec2& _size)
	: position(pos), size(_size) {

}

ViewPort::ViewPort(const vec2& _size)
	: position(0.0f), size(_size) {

}

void ViewPort::setCenter(const vec2& mid) {
	position = mid - size * 0.5;
}

void ViewPort::setCenter(const vec2& mid, const vec2& _size) {
	size = _size;
	position = mid - size * 0.5;
}

vec2 ViewPort::getCenter() const {
	return position + size * 0.5;
}

#include "stdafx.h"
#include "Color.h"

Color::Color() { r = g = b = 0.0f; }
Color::Color(float v) { r = g = b = v; }
Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}; 
Color::~Color() {};

Color Color::unit() const {
	float length = this->intensity();
	return Color(r/length, g/length, b/length);
}

float Color::intensity() const {
	return sqrt(intensity2());
}

float Color::intensity2() const {
	return (r*r + g*g + b*b);
}


Color Color::operator+(Color::i x) const {
	return Color(r+x.r, g+x.g, b+x.b);
}

Color Color::operator-() const {
	return Color(-r, -g, -b);
}

Color Color::operator-(Color::i x) const {
	return (*this)+(-x);
}

Color Color::operator*(Color::i x) const {
	return Color(r*x.r, g*x.g, b*x.b);
}

Color Color::operator/(Color::i x) const {
	return Color(r/x.r, g/x.g, b/x.b);
}

bool Color::operator==(Color::i x) const {
	return r==x.r && g==x.g && b==x.b;
}

bool Color::operator!=(Color::i x) const {
	return !((*this)==x);
}


std::ostream& operator<<(std::ostream& s, Color& c) {
	s << "(" << c.r << " " << c.g << " " << c.b << ")";
	return s;
}

/** Basic Colors **/
const Color
	Color::black(0.f),
	Color::white(1.f),
	Color::gray(0.7f),
	Color::darkGray(0.2f),
	Color::red(0.95f, 0.32f, 0.23f),
	Color::green(0.71f, 0.89f, 0.1f),
	Color::blue(0.19f, 0.77f, 0.98f),
	Color::darkBlue(0.04f, 0.42f, 0.5f),
	Color::yellow(1.0f, 0.98f, 0.74f);
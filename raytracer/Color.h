#pragma once

class Color
{
public:
	typedef const Color i; //input vector
	typedef Color& io;

	float r, g, b;

	Color();
	Color(float v);
	Color(float r, float g, float b);
	~Color();

	Color unit() const;

	float intensity() const;
	float intensity2() const;

	Color operator+(Color::i) const;
	Color operator-() const;
	Color operator-(Color::i) const;
	Color operator*(Color::i) const;
	Color operator/(Color::i) const;

	bool operator==(Color::i) const;
	bool operator!=(Color::i) const;

	friend std::ostream& operator<<(std::ostream& s, Color& c);

	static const Color black, white, gray, darkGray, red, green, blue, darkBlue, yellow;
};




#pragma pack(push, 1)
class ColorRGB {
	uint8 r, g, b;
public:
	ColorRGB() { r=g=b=0; }
	ColorRGB(Color c) {
		r = uint8(clamp(0.f, c.r, 1.f) * 255);
		g = uint8(clamp(0.f, c.g, 1.f) * 255);
		b = uint8(clamp(0.f, c.b, 1.f) * 255);
	}
};
#pragma pack(pop)
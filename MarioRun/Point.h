#pragma once
struct Point
{
public:
	Point();
	Point(const Point& point);
	Point(const Size& size);
	Point(float x, float y);
	~Point();

	Point operator+(const Point& point) const;
	Point operator-(const Point& point) const;
	Point operator*(const Point& point) const;
	Point operator*(const float amount) const;
	Point operator/(const Point& point) const;
	Point operator/(const float amount) const;

	bool Equals(const Point& point) const;

	static float Distance(const Point& a, const Point & b);

public:
	float x;
	float y;
};


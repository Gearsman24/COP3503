#pragma once
#include <iostream>
#include <math.h>
#define PI 3.14159f
using namespace std;

/* Base Class */
class Shape
{
public:
	virtual void Scale(float scaleFactor) = 0;
	virtual void Display() const = 0;

	virtual ~Shape() = 0;
};

/* Base 2D Class */
class Shape2D : virtual public Shape
{
public:

	virtual float Area() const = 0;
	void ShowArea() const;

	virtual string GetName2D() const = 0;

	bool operator>(const Shape2D& rhs) const;
	bool operator<(const Shape2D& rhs) const;
	bool operator==(const Shape2D& rhs) const;
};

/* Child 2D Classes */
class Square : public Shape2D
{
private:
	float length;
	string name;
public:
	Square();
	Square(float pLength);

	void Scale(float scaleFactor);
	void Display() const;

	float Area() const;
	string GetName2D() const;
};

class Triangle : public Shape2D
{
private:
	float base, height;
	string name;
public:
	Triangle();
	Triangle(float pBase, float pHeight);

	void Scale(float scaleFactor);
	void Display() const;

	float Area() const;
	string GetName2D() const;
};

class Circle : public Shape2D
{
private:
	float radius;
	string name;
public:
	Circle();
	Circle(float pRadius);

	void Scale(float scaleFactor);
	void Display() const;

	float Area() const;
	string GetName2D() const;
};

/* Base 3D Class */
class Shape3D : virtual public Shape
{
public: 
	virtual float Volume() const = 0;
	void ShowVolume() const;

	virtual string GetName3D() const = 0;

	bool operator>(const Shape3D& rhs) const;
	bool operator<(const Shape3D& rhs) const;
	bool operator==(const Shape3D& rhs) const;
};

/* Child 3D Classes */
class TriangularPyramid : public Shape3D, private Triangle
{
private:
	Triangle* triangle;
	float height;
	string name;
public:
	TriangularPyramid();
	TriangularPyramid(float pHeight, float pBaseLength, float pBaseHeight);

	void Scale(float scaleFactor);
	void Display() const;

	float Volume() const;
	string GetName3D() const;
};

class Cylinder : public Shape3D, private Circle
{
private:
	Circle* circle;
	float height;
	string name;
public:
	Cylinder();
	Cylinder(float pHeight, float pRadius);

	void Scale(float scaleFactor);
	void Display() const;

	float Volume() const;
	string GetName3D() const;
};

class Sphere : public Shape3D, private Circle
{
private:
	Circle* circle;
	float radius;
	string name;
public:
	Sphere();
	Sphere(float pRadius);

	void Scale(float scaleFactor);
	void Display() const;

	float Volume() const;
	string GetName3D() const;
};
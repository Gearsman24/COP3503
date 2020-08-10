#include "Shapes.h"

/* DESTRUCTOR */
Shape::~Shape()
{

}

/* SHAPE 2D FUNCTIONS */
void Shape2D::ShowArea() const
{
	cout << "The area of the " + GetName2D() + " is : " << Area() << endl;
}

bool Shape2D::operator>(const Shape2D& rhs) const
{
	if (this->Area() > rhs.Area())
		return true;
	return false;
}
bool Shape2D::operator<(const Shape2D& rhs) const
{
	if (this->Area() < rhs.Area())
		return true;
	return false;
}
bool Shape2D::operator==(const Shape2D& rhs) const
{
	if (this->Area() == rhs.Area())
		return true;
	return false;
}

/* SQUARE FUNCTIONS */
Square::Square()
{
	name = "Square";
	length = 0;
}
Square::Square(float pLength)
{
	name = "Square";
	length = pLength;
}

void Square::Scale(float scaleFactor)
{
	length = length * scaleFactor;
}
void Square::Display() const
{
	cout << "The area of the " + name + " is : " << Area() << endl;
	cout << "Length of a side: " << length << endl;
}

float Square::Area() const
{
	return length * length;
}
string Square::GetName2D() const
{
	return name;
}

/* TRIANGLE FUNCTIONS */
Triangle::Triangle()
{
	name = "Triangle";
	base = 0;
	height = 0;
}
Triangle::Triangle(float pBase, float pHeight)
{
	name = "Triangle";
	base = pBase;
	height = pHeight;
}

void Triangle::Scale(float scaleFactor)
{
	base = base * scaleFactor;
	height = height * scaleFactor;
}
void Triangle::Display() const
{
	cout << "The area of the " + name + " is : " << Area() << endl;
	cout << "Base: " << base << endl;
	cout << "Height: " << height << endl;
}

float Triangle::Area() const
{
	return (base * height) / 2;
}
string Triangle::GetName2D() const
{
	return name;
}

/* CIRCLE FUNCTIONS */
Circle::Circle()
{
	name = "Circle";
	radius = 0;
}
Circle::Circle(float pRadius)
{
	name = "Circle";
	radius = pRadius;
}

void Circle::Scale(float scaleFactor)
{
	radius = radius * scaleFactor;
}
void Circle::Display() const
{
	cout << "The area of the " + name + " is : " << Area() << endl;
	cout << "Radius: " << radius << endl;
}

float Circle::Area() const
{
	return PI * radius * radius;
}
string Circle::GetName2D() const
{
	return name;
}


/* SHAPE 3D FUNCTIONS */
void Shape3D::ShowVolume() const
{
	cout << "The volume of the " + GetName3D() + " is : " << Volume() << endl;
}

bool Shape3D::operator>(const Shape3D& rhs) const
{
	if (this->Volume() > rhs.Volume())
		return true;
	return false;
}
bool Shape3D::operator<(const Shape3D& rhs) const
{
	if (this->Volume() < rhs.Volume())
		return true;
	return false;
}
bool Shape3D::operator==(const Shape3D& rhs) const
{
	if (this->Volume() == rhs.Volume())
		return true;
	return false;
}

/* TRIANGULAR PYRAMID FUNCTIONS */
TriangularPyramid::TriangularPyramid()
{
	name = "Triangular Pyramid";
	triangle = new Triangle();
	height = 0;
}
TriangularPyramid::TriangularPyramid(float pHeight, float pBaseLength, float pBaseHeight)
{
	name = "Triangular Pyramid";
	triangle = new Triangle(pBaseLength, pBaseHeight);
	height = pHeight;
}

void TriangularPyramid::Scale(float scaleFactor)
{
	triangle->Scale(scaleFactor);
	height = height * scaleFactor;
}
void TriangularPyramid::Display() const
{
	cout << "The volume of the " + name + " is : " << Volume() << endl;;
	cout << "The height is: " << height << endl;
	triangle->Display();
}

float TriangularPyramid::Volume() const
{
	return height * triangle->Area() / 3;
}
string TriangularPyramid::GetName3D() const
{
	return name;
}

/* CYLINDER FUNCTIONS */
Cylinder::Cylinder()
{
	name = "Cylinder";
	circle = new Circle();
	height = 0;
}
Cylinder::Cylinder(float pHeight, float pRadius)
{
	name = "Cylinder";
	circle = new Circle(pRadius);
	height = pHeight;
}

void Cylinder::Scale(float scaleFactor)
{
	circle->Scale(scaleFactor);
	height = height * scaleFactor;
}
void Cylinder::Display() const
{
	cout << "The volume of the " + name + " is : " << Volume() << endl;
	cout << "The height is: " << height << endl;
	circle->Display();
}

float Cylinder::Volume() const
{
	return circle->Area() * height;
}
string Cylinder::GetName3D() const
{
	return name;
}

/* SPHERE FUNCTIONS */
Sphere::Sphere()
{
	name = "Sphere";
	circle = new Circle();
	radius = 0;
}
Sphere::Sphere(float pRadius)
{
	name = "Sphere";
	circle = new Circle(pRadius);
	radius = pRadius;
}

void Sphere::Scale(float scaleFactor)
{
	circle->Scale(scaleFactor);
	radius = radius * scaleFactor;
}
void Sphere::Display() const
{
	cout << "The volume of the " + name + " is :" << Volume() << endl;
	circle->Display();
}

float Sphere::Volume() const
{
	return 4 * circle->Area() * radius / 3;
}
string Sphere::GetName3D() const
{
	return name;
}
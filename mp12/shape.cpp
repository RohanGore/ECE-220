#define _USE_MATH_DEFINES

#include "shape.hpp"



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 

Shape::Shape(string name)
{
	name_ = name; // Set member variable to name
}

string Shape::getName()
{
	return name_; // Return name of the shape
}


//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Rectangle::Rectangle(double width, double length):Shape("Rectangle") // Call base class constructor
{
	width_ = width; // Set member variable to width
	length_ = length; // Set member variable to length
}

double Rectangle::getArea() const
{
	return width_ * length_; // Calculate area of rectangle
}

double Rectangle::getVolume() const
{
	return 0; // Volume of rectangle is 0
}

Rectangle Rectangle::operator + (const Rectangle& rec)
{
	double newLength = this->getLength() + rec.getLength(); // Add length of current object and other object
	double newWidth = this->getWidth() + rec.getWidth(); // Add width of current object and other object

	Rectangle rect(newWidth, newLength); // Create new object with new values

	return rect; // Return new object
}

Rectangle Rectangle::operator - (const Rectangle& rec)
{
	double newLength = this->getLength() - rec.getLength(); // Subtract length of other object from current object
	double newWidth = this->getWidth() - rec.getWidth(); // Subtract width of other object from current object
	if(newLength < 0)
		newLength = 0; // If newLength is less than 0, set it to 0
	if(newWidth < 0)
		newWidth = 0; // If newWidth is less than 0, set it to 0

	Rectangle rect(newWidth, newLength); // Create new object with new values

	return rect; // Return new object
}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Circle::Circle(double radius):Shape("Circle") // Call base class constructor
{
	radius_ = radius; // Set member variable to radius
}

double Circle::getArea() const
{
	return (radius_ * radius_) * M_PI; // Calculate area of circle
}

double Circle::getVolume() const
{
	return 0; // Volume of circle is 0
}

Circle Circle::operator + (const Circle& cir)
{
	double newRadius = this->getRadius() + cir.getRadius(); // Add radius of current object and other object

	Circle circ(newRadius); // Create new object with new values

	return circ; // Return new object
}

Circle Circle::operator - (const Circle& cir)
{
	double newRadius = this->getRadius() - cir.getRadius(); // Subtract radius of other object from current object
	
	if(newRadius < 0) // If newRadius is less than 0, set it to 0
		newRadius = 0;

	Circle circ(newRadius); // Create new object with new values

	return circ; // Return new Object
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Sphere::Sphere(double radius):Shape("Sphere") // Call base class constructor
{
	radius_ = radius; // Set member variable to radius
}

double Sphere::getArea() const
{
	return 4.0 * M_PI * (radius_ * radius_); // Calculate surface area of sphere
}

double Sphere::getVolume() const
{
	return (4.0 / 3.0) * (radius_ * radius_ * radius_) * M_PI; // Calculate volume of sphere
}

Sphere Sphere::operator + (const Sphere& sph)
{
	double newRadius = this->getRadius() + sph.getRadius(); // Add radius of current object to other object

	Sphere sphere(newRadius); // Make new object with new value

	return sphere; // Return new object
}

Sphere Sphere::operator - (const Sphere& sph)
{
	double newRadius = this->getRadius() - sph.getRadius(); // Subtract other object's radius from current object

	if(newRadius < 0) // If newRadius is less than 0, set it to 0
		newRadius = 0;

	Sphere sphere(newRadius); // Create new object with new values

	return sphere; // Return new object
}

double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism") // Call base class constructor
{
	width_ = width; // Set member variable to width
	length_ = length; // Set member variable to length
	height_ = height; // Set member variable to height
}

double RectPrism::getArea() const
{
	return 2.0 * (length_ *  width_  + length_ * height_ + width_ * height_); // Calculate surface area of rectangular prism
}

double RectPrism::getVolume() const
{
	return length_ * width_ * height_; // Calculate volume of rectangular prism
}

RectPrism RectPrism::operator + (const RectPrism& rectp)
{
	double newWidth = this->getWidth() + rectp.getWidth(); // Add current object's width to other object
	double newLength = this->getLength() + rectp.getLength(); // Add current object's length to other object
	double newHeight = this->getHeight() + rectp.getHeight(); // Add current object's height to other object

	RectPrism RectPrism(newWidth, newLength, newHeight); // Create new object with new values

	return RectPrism; // Return new object
}

RectPrism RectPrism::operator - (const RectPrism& rectp)
{
	double newWidth = this->getWidth() - rectp.getWidth(); // Subtract other object's width from current object
	double newLength = this->getLength()- rectp.getLength(); // Subtract other object's length from current object
	double newHeight = this->getHeight() - rectp.getHeight(); // Subtract other object's height from current object

	if(newLength < 0) // If newLength is less than 0, set it to 0
		newLength = 0;
	if(newWidth < 0) // If newWidth is less than 0, set it to 0
		newWidth = 0;
	if(newHeight < 0) // If newHeight is less than 0, set it to 0
		newHeight = 0;


	RectPrism RectPrism(newWidth, newLength, newHeight); // Create new object with new values

	return RectPrism; // Return new object
}

double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
	ifstream fin(file_name); // Create ifstream and open file
	
	vector<Shape*> shapes; // Create new vector of shape pointers

	int numObjects; // Declare variable to hold number of objects

	fin >> numObjects; // Read number of objects from file

	string name; // Declare variable to hold name of shape

	double radius, width, length, height; // Declare variables to hold radius, width, length, and height
	
	int i; // Declare loop variable

	for(i = 0; i < numObjects; i++) // Loop through each shape
	{

		fin >> name; // Read name of shape from file

		if(name == "Rectangle") // Check if shape is rectangle
		{
			fin >> width >> length; // Read length and width from file
			Shape * rect = new Rectangle(width, length); // Create shape pointer with correct dimensions
			shapes.push_back(rect); // Push shape pointer onto vector
		}
		else if(name == "Circle") // Check if shape is circle
		{
			fin >> radius; // Read radius from file
			Shape * circ = new Circle(radius); // Create shape pointer with correct dimensions
			shapes.push_back(circ); // Push shape pointer onto vector
		}
		else if(name == "Sphere") // Check if shape is a sphere
		{
			fin >> radius; // Read radius from file
			Shape * sphe = new Sphere(radius); // Create shape pointer with correct dimensions
			shapes.push_back(sphe); // Push shape pointer onto vector
		}
		else if(name == "RectPrism") // Check if shape is a rectangular prism
		{
			fin >> width >> length >> height; // Read length, width and height from file
			Shape * rectp = new RectPrism(width, length, height); // Create shape pointer with correct dimensions
			shapes.push_back(rectp); // Push shape pointer onto vector
		}
	}
	fin.close(); // Close the file

	return shapes; // Return the vector
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	int numObjects = shapes.size(); // Declare variable and initialize to number of objects
	int i; // Declare loop variable
	for(i = 0; i < numObjects; i++) // Loop through vector
	{
		if(shapes[i]->getArea() > max_area) // Check if area of current object is greater than the current max area
			max_area = shapes[i]->getArea(); // If it is, set new max_area to area of current object
	}
	return max_area; // Return the max_area
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	int numObjects = shapes.size(); // Declare variable and initialize to number of objects
	int i; // Declare loop variable
	for(i = 0; i < numObjects; i++) // Loop through vector
	{
		if(shapes[i]->getVolume() > max_volume) // Check if volume of current object is greater than the current max volume
			max_volume = shapes[i]->getVolume(); // If it is, set new max_volume to area of current object
	}
	
	return max_volume; // Return the max_volume
}


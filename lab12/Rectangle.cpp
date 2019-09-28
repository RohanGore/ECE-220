#include "Rectangle.h"

//Empty Constructor sets instantiates a rectangle with length and width set as 0
Rectangle::Rectangle(){
//INSERT YOUR CODE HERE:
	set_length(0);
	set_width(0);
}

//Standard Constructor sets instantiates a rectangle with length and width set as input values
Rectangle::Rectangle(int input_length, int input_width){
//INSERT YOUR CODE HERE:
	set_length(input_length);
	set_width(input_width);
}

//Copy Constructor
//Instantiate a rectangle with length R1 = length R2 and width R1 = width R2
Rectangle::Rectangle( const Rectangle& other ){
//INSERT YOUR CODE HERE:
	set_length(other.get_length());
	set_width(other.get_width());
}

//Setter and Getter functions
void Rectangle::set_length(int input_length){
//INSERT YOUR CODE HERE:
	if(input_length >= 0)	
		length = input_length;
	else
		length = 0;
}

void Rectangle::set_width(int input_width){
//INSERT YOUR CODE HERE:
	if(input_width >= 0)
		width = input_width;
	else
		length = 0;
}

int Rectangle::get_length(void) const{
//INSERT YOUR CODE HERE:
	return length;
}

int Rectangle::get_width(void) const{
//INSERT YOUR CODE HERE:
	return width;
}

//Calculate Area of rectangle
int Rectangle::area(void){
//INSERT YOUR CODE HERE:
	int result = get_length() * get_width();
	return result;
}

//Calculate Perimeter of rectangle
int Rectangle::perimeter(void){
//INSERT YOUR CODE HERE:
	int result = 2 * get_length() + 2 * get_width();
	return result;
}

/*Addition operator overload
* We define addition of two rectangles to be as follows: R3 = R1 + R2
* where length of R3 = length R1 + length R2
* and width R3 = width R1 + width R2
*/
Rectangle Rectangle::operator + (const Rectangle& other){
//INSERT YOUR CODE HERE:
	Rectangle rect;

	int newLength = this->get_length() + other.get_length();
	rect.set_length(newLength);

	int newWidth = this->get_width() + other.get_width();
	rect.set_width(newWidth);

	return rect;
}

/*Multiplication operator overload
* We define addition of two rectangles to be as follows: R3 = R1 * R2
* where length of R3 = length R1 * length R2
* and width R3 = width R1 * width R2
*/
Rectangle Rectangle::operator * (const Rectangle& other){
//INSERT YOUR CODE HERE:
	Rectangle rect;

	int newLength = this->get_length() * other.get_length();
	rect.set_length(newLength);

	int newWidth = this->get_width() * other.get_width();
	rect.set_width(newWidth);

	return rect;
}

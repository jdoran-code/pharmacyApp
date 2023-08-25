//
// Created by Justin Doran on 7/29/23.
//

#include <string>
#include <cmath>
using namespace std;

class Rectangle {
private:
    double length;
    double width;
public:
    Rectangle(double theLength, double theWidth);

    double getLength() const {return length;}

    double getWidth() const {return width;}

    double getArea() const {return length * width;}

    void setLength(double length) {this->length = length;}

    void setWidth(double width) {this->width = width;}

    void setArea(double area);

    void grow(double lenTimes, double widTimes);

    void shrink(double lenTimes, double widTimes);
};

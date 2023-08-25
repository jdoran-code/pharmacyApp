//
// Created by Justin Doran on 7/29/23.
//

#include "Rectangle.h"

Rectangle::Rectangle(double theLength, double theWidth) {
    length = theLength;
    width = theWidth;
}

void Rectangle::setArea(double area) {
    this->length = sqrt(area);
    this->width = sqrt(area);
}

void Rectangle::grow(double lenTimes, double widTimes) {
    this->length *= lenTimes;
    this->width *= widTimes;
}

void Rectangle::shrink(double lenTimes, double widTimes) {
    this->length /= lenTimes;
    this->width /= widTimes;
}

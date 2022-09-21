#include "Vec2.h"
#include <cmath>

#include <iostream>

Vec2::Vec2() {

    this->x = 0;
    this->y = 0;

}

Vec2::Vec2(float x, float y) {

    this->x = x;
    this->y = y;

}

Vec2 Vec2::MultScaVec2(float scalar) {

    Vec2 mult;

    mult.x = this->x * scalar;
    mult.y = this->y * scalar;

    return mult;

}

float Vec2::ModVec2() {

    float mod;

    mod = sqrt(pow(this->x,2) + pow(this->y,2));

    return mod;

}

Vec2 Vec2::UnitVec2() {

    Vec2 unit;
    float mod = this->ModVec2();
    if (mod == 0) return Vec2(0,0);

    unit.x = this->x / mod;
    unit.y = this->y / mod;

    return unit;

}

float Vec2::DistVec2(Vec2 vetor) {

    Vec2 aux;

    aux = *this - vetor;
    
    return aux.ModVec2();

}

float Vec2::DegVec2() {

    float deg;

    deg = atan2(this->y,this->x) * (180/M_PI);

    //Adjust the angle if y is negative, in this case it would be the same as the positive angle
    if (this->y < 0) deg += 360; 

    return deg;

}

float Vec2::DegPntsVec2(Vec2 vetor) {

    Vec2 line =  *this - vetor;

    return line.DegVec2();

}

Vec2 Vec2::RotateVec2(float degree) {

    Vec2 rotatedVec2;
    float radian = degree * (M_PI/180);

    rotatedVec2.x = (this->x * cos(radian)) - (this->y * sin(radian));
    rotatedVec2.y = (this->y * cos(radian)) + (this->x * sin(radian));

    return rotatedVec2;

}

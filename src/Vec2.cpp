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
/*
Vec2 Vec2::SumVec2(Vec2 vetor) {

    Vec2 sum;

    sum.x = this->x + vetor.x;
    sum.y = this->y + vetor.y;

    return sum;

}
*/

/*
Vec2 Vec2::SubVec2(Vec2 vetor) {

    Vec2 sub;

    sub.x = this->x - vetor.x;
    sub.y = this->y - vetor.y;

    return sub;

}
*/

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

    unit.x = this->x / mod;
    unit.y = this->y / mod;

    return unit;

}

float Vec2::DistVec2(Vec2 vetor) {

    Vec2 aux;

    aux = *this - vetor;
    //aux = this->SubVec2(vetor);
    
    return aux.ModVec2();

}

float Vec2::DegVec2() {

    float deg;

    deg = atan2(this->y,this->x) * (180/M_PI);

    if (this->y < 0) deg += 360; 

    return deg;

}

float Vec2::DegPntsVec2(Vec2 vetor) {

    //Vec2 line = this->SubVec2(vetor);
    Vec2 line =  *this - vetor;

    return line.DegVec2();

}

Vec2 Vec2::RotateVec2(float degree) {

    Vec2 rotatedVec2;
    float radian = degree * (M_PI/180);

    std::cout << radian << "\n";
    std::cout << cos(radian) << "\n";

    //Multiplies the formulas by -1 because its used a positive y-axis downwards
    rotatedVec2.x = (this->x * cos(radian)) + (this->y * sin(radian));
    rotatedVec2.y = (this->y * cos(radian)) - (this->x * sin(radian));

    return rotatedVec2;

}

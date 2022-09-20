#ifndef VEC2_H
#define VEC2_H

//Class that store and manipulate a 2d vector
class Vec2 {

    public:

        float x;
        float y;

        Vec2();
        Vec2(float x, float y);
        
        //Definition of methods to three c++ operators
        Vec2 operator + (Vec2 vetor) const {

            Vec2 sum;

            sum.x = this->x + vetor.x;
            sum.y = this->y + vetor.y;

            return sum;

        }

        Vec2 operator - (Vec2 vetor) const {

            Vec2 sub;

            sub.x = this->x - vetor.x;
            sub.y = this->y - vetor.y;

            return sub;

        }

        Vec2 operator * (float scalar) const {

            Vec2 mul;

            mul.x = this->x*scalar;
            mul.y = this->y*scalar;

            return mul;

        }

        void operator = (Vec2 vetor) {

           this->x = vetor.x;
           this->y = vetor.y; 

           return;

        } 

        //Multiplies the vector by a scalar
        Vec2 MultScaVec2(float scalar);
        //Returns the vector absolute value
        float ModVec2();
        //Returns a unit vector based on the Vec2 stored
        Vec2 UnitVec2();
        //Calculate the distance between two vectors
        float DistVec2(Vec2 vetor);
        //Return the degree of the vector
        float DegVec2();
        //Return the degree of the slope between two points )
        float DegPntsVec2(Vec2 vetor);
        //Rotate the vector in a given degree
        Vec2 RotateVec2(float degree);

};


#endif
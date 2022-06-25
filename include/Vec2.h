#ifndef VEC2_H
#define VEC2_H

class Vec2 {

    public:

        float x;
        float y;

        Vec2();
        Vec2(float x, float y);

        Vec2 operator + (Vec2 vetor) {

            Vec2 sum;

            sum.x = this->x + vetor.x;
            sum.y = this->y + vetor.y;

            return sum;

        }

        Vec2 operator - (Vec2 vetor) {

            Vec2 sub;

            sub.x = this->x - vetor.x;
            sub.y = this->y - vetor.y;

            return sub;

        }

        void operator = (Vec2 vetor) {

           this->x = vetor.x;
           this->y = vetor.y; 

           return;

        }

        Vec2 MultScaVec2(float scalar);
        float ModVec2();
        Vec2 UnitVec2();
        float DistVec2(Vec2 vetor);
        float DegVec2();
        float DegPntsVec2(Vec2 vetor);
        Vec2 RotateVec2(float degree);

};


#endif
#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

//This class represents a rectangle size and position
class Rect {

    public: 

        float x;
        float y;
        float w;
        float h;

        void operator = (Rect rect) {

            this->x = rect.x;
            this->y = rect.y;
            this->w = rect.w;
            this->h = rect.h;

        }

        Rect();
        Rect(float x, float y, float w, float h);

        //Sum vector components to Rect position
        void RectVec2Sum(Vec2 vetor);
        //Returns the positon of Rect center
        Vec2 RectCenter();
        //Calculate the distance between two Rects center
        float RectCenterDist(Rect rect);
        //Check if a given point is inside of a Rect
        bool PointInRect(Vec2 point);

};


#endif
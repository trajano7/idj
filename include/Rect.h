#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {

    public: 

        float x;
        float y;
        float w;
        float h;

        Rect();
        Rect(float x, float y, float w, float h);

        void RectVec2Sum(Vec2 vetor);
        Vec2 RectCenter();
        float RectCenterDist(Rect rect);
        bool PointInRect(Vec2 point);

};


#endif
#include "Rect.h"

Rect::Rect() {

    x = 0;
    y = 0;
    w = 0;
    h = 0;

}

Rect::Rect(float x, float y, float w, float h) {

    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

}

void Rect::RectVec2Sum(Vec2 vetor) {

    this->x += vetor.x;
    this->y += vetor.y;

    return; 

}

Vec2 Rect::RectCenter() {

    Vec2 rectCenter;

    rectCenter.x = this->x + (this->w / 2);
    rectCenter.y = this->y - (this->h / 2);

    return rectCenter;

}

float Rect::RectCenterDist(Rect rect) {

    Vec2 rectCenter1, rectCenter2; 
    float rectCenterDist;

    rectCenter1 = this->RectCenter();
    rectCenter2 = rect.RectCenter();

    rectCenterDist = rectCenter1.DistVec2(rectCenter2);

    return rectCenterDist;

}

bool Rect::PointInRect(Vec2 point) {

    if (point.x >= this->x && point.x <= this->x + this->w) {
        if (point.y <= this->y && point.y >= this->y - this->h) {
            return true;
        }
    }

    return false;

}

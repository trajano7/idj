#include "Collider.h"

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated) {

    this->scale = scale;
    this->offset = offset;

}

void Collider::Update(float dt) {

    box.w = associated.box.w*scale.x;
    box.h = associated.box.h*scale.y;
    offset = offset.RotateVec2(associated.angleDeg);
    box.x = (associated.box.RectCenter().x + offset.x) - box.w/2;
    box.y = (associated.box.RectCenter().y + offset.y) - box.h/2;

}


void Collider::Start() {

}

void Collider::Render() {

	//Show the colliders for debug purpose
	#ifdef DEBUG
		Vec2 center( box.RectCenter() );
		SDL_Point points[5];
	
		Vec2 point = (Vec2(box.x, box.y) - center).RotateVec2( associated.angleDeg )
						+ center - Camera::pos;
		points[0] = {(int)point.x, (int)point.y};
		points[4] = {(int)point.x, (int)point.y};
		
		point = (Vec2(box.x + box.w, box.y) - center).RotateVec2( associated.angleDeg )
						+ center - Camera::pos;
		points[1] = {(int)point.x, (int)point.y};
		
		point = (Vec2(box.x + box.w, box.y + box.h) - center).RotateVec2( associated.angleDeg )
						+ center - Camera::pos;
		points[2] = {(int)point.x, (int)point.y};
		
		point = (Vec2(box.x, box.y + box.h) - center).RotateVec2( associated.angleDeg )
						+ center - Camera::pos;
		points[3] = {(int)point.x, (int)point.y};
	
		SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
	#endif // DEBUG

}

bool Collider::Is(string type) {
    
    if("Collider" == type) {
        return true;
    }

    return false;

}

void Collider::SetScale(Vec2 scale) {

    this->scale = scale;

}

void Collider::SetOffset(Vec2 offset) {

    this->offset = offset;

}
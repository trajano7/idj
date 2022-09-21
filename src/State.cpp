#include "State.h"

#define INCLUDE_SDL 
#include "SDL_include.h"

State::State() {

    popRequested = false;
    quitRequested = false;
    started = false;

}

State::~State() {

    objectArray.clear();

}

weak_ptr<GameObject> State::AddObject(GameObject* object) {

    shared_ptr<GameObject> newObject(object);
	objectArray.push_back(newObject);
	if(started) newObject->Start();
	weak_ptr<GameObject> weakPtr(newObject);

	return weakPtr;

}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* object) {

    for (int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get() == object) {
			weak_ptr<GameObject> weakPtr(objectArray[i]);
			return weakPtr;
		}
	}

	weak_ptr<GameObject> weakPtr;
	return weakPtr;

}

void State::StartArray() {

	for (int i; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}

}

void State::UpdateArray(float dt) {

	for (int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}

}

void State::RenderArray() {

	for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}

}

bool State::PopRequested() {

    return popRequested;

}

bool State::QuitRequested() {

    return quitRequested;

}
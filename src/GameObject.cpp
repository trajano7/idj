#include "GameObject.h"

#include <algorithm>
#include <typeinfo>

GameObject::GameObject() {

    isDead = false;

}

GameObject::~GameObject() {

    vector<Component*>::iterator it;

    for (it = components.end(); it > components.begin(); it--) {
        delete *it;
    }

    components.clear();

}

void GameObject::Update(float dt) {

    vector<Component*>::iterator it;

    for (it = components.begin(); it < components.end(); it++) {
        (*it)->Update(dt);
    }

    return;

}

void GameObject::Render() {

    vector<Component*>::iterator it;

    for (it = components.begin(); it < components.end(); it++) {
        (*it)->Render();
    }

    return;

}

bool GameObject::IsDead() {

    return isDead;

}

void GameObject::RequestDelete() {

    isDead = true;

}

void GameObject::AddComponent(Component* cpt) {

    components.push_back(cpt);

    return;

}

void GameObject::RemoveComponent(Component* cpt) {

    vector<Component*>::iterator it;

    it = find(components.begin(),components.end(),cpt);
    if (it != components.end()) {
        delete *it;
        components.erase(it);
    }

    return;

} 

Component* GameObject::GetComponent(string type) {

    string type_aux = type;
    vector<Component*>::iterator it;

    //Concatenete the number of char to the type to match typeid pattern
    type_aux.insert(0,to_string(type.size()));

    for (it = components.begin(); it < components.end(); it++) {
        if(typeid(**it).name() == type_aux) {
            return *it;
        }
    }

    return nullptr;

}
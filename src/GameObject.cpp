#include "GameObject.h"

#include "Component.h"

#include <algorithm>
#include <typeinfo>

GameObject::GameObject() {

    isDead = false;
    started = false;
    angleDeg = 0;

}

GameObject::~GameObject() {

    components.clear();

}

void GameObject::Start() {

    for (int i=0; i<components.size(); i++) {
        components[i]->Start();
    }
    started = true;

    return;

}

void GameObject::Update(float dt) {

    vector<unique_ptr<Component>>::iterator it;

    for (it = components.begin(); it < components.end(); it++) {
        (*it)->Update(dt);
    }

    return;

}

void GameObject::Render() {

    vector<unique_ptr<Component>>::iterator it;

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

    if(started) cpt->Start();
    components.emplace_back(cpt);

    return;

}

void GameObject::RemoveComponent(Component* cpt) {

    vector<unique_ptr<Component>>::iterator it;

    for (it = components.begin(); it < components.end(); it++) {
        if(typeid(**it).name() == typeid(*cpt).name()) {
           components.erase(it); 
        }
    }

    return;

} 

Component* GameObject::GetComponent(string type) {

    string type_aux = type;
    vector<unique_ptr<Component>>::iterator it;

    //Concatenete the number of char to the type to match typeid string pattern
    type_aux.insert(0,to_string(type.size()));

    for (it = components.begin(); it < components.end(); it++) {
        if(typeid(**it).name() == type_aux) {
            return it->get();
        }
    }

    return nullptr;

}

void GameObject::NotifyCollision(GameObject& other) {

    vector<unique_ptr<Component>>::iterator it;

    //Notify all it components that a collision occurred
    for (it = components.begin(); it < components.end(); it++) {
        (*it)->NotifyCollision(other);
    }

}
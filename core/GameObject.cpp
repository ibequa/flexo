//
//  GameObject.cpp
//  Flexo
//
//  Created by Ilya on 10/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#include <algorithm>

#include "GameObject.hpp"
#include "Transform.hpp"

GameObject::GameObject(const params& p) : _initParams(p) {
    _transform = &addComponent<Transform>({"Transform", this});
}

GameObject::~GameObject() {
    for (auto& x : _components)
        delete x.second;
}

Component* GameObject::findComponent(const_str& name) const {
    auto comp = _components.find(name);
    
    assert(comp != _components.end());
    return comp->second;
}

bool GameObject::hasComponent(const_str& name) const {
    return (_components.find(name) == _components.end()) ? false : true;
}

void GameObject::removeComponent(const_str& name) {
    auto comp = _components.find(name);
    
    assert(comp != _components.end());
    
    delete comp->second;
    _components.erase(comp);
}

void addChild_(GameObject& to, GameObject& child) {
    assert(to.getName() != child.getName());
    
    if (child._parent)
        detachChildRecursively_(*child._parent, child);
    
    child._parent = &to;
    to._children.push_back(&child);
}

void detachChild_(GameObject& from, GameObject& child) {
    auto it = std::find(from._children.begin(), from._children.end(), &child);
    
    assert((from.getName() != child.getName()) && (it != from._children.end()));
    
    from._children.erase(it);
    
    if (from._parent != nullptr)
        addChild_(*from._parent, child);
    else
        child._parent = nullptr;
}

void detachChildRecursively_(GameObject& parent, GameObject& child) {
    auto it = std::find(parent._children.begin(), parent._children.end(), &child);
    
    assert((parent.getName() != child.getName()) && (it != parent._children.end()));
    
    parent._children.erase(it);
    child._parent = nullptr;
}

GameObject* GameObject::findChild(const_str& name) const {
    for (const auto& child : _children)
        if (child->getName() == name)
            return child;
    return nullptr;
}

bool GameObject::hasChild(const_str& name) const {
    auto it = std::find_if(_children.cbegin(), _children.cend(), [&name] (const GameObject* g) { return (g->getName() == name) ? true : false; });
    return (it == _children.cend()) ? false : true;
}

bool hasChildRecursively_(const GameObject& parent, GameObject::const_str& name) {
    for (const auto& child : parent._children) {
        hasChildRecursively_(*child, name);
        if (parent.getName() == name)
            return true;
    }
    return false;
}

GameObject* GameObject::findChildRecursively(GameObject& from, const_str& name) const {
    for (const auto& child : from._children) {
        findChildRecursively(*child, name);
        if (from.getName() == name)
            return &from;
    }
    return nullptr;
}
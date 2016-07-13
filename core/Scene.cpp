//
//  Scene.cpp
//  Flexo
//
//  Created by Ilya on 12/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#include "Scene.hpp"
#include "ResourceManager.hpp"

Scene::str_gameobjptr_map Scene::_gameObjects;

Scene::Scene(const_str& name, int id) : _name(name), _id(id) {}

Scene::~Scene() {
    for (auto it = _gameObjects.cbegin(); it != _gameObjects.cend(); ) {
        if (it->second->isPersistent())
            ++it;
        else {
            delete it->second;
            _gameObjects.erase(it++);
        }
    }
    ResourceManager::freeAllEver();
}

GameObject* Scene::findGameObject(const_str& name) {
    auto it = _gameObjects.find(name);
    assert(it != _gameObjects.end());
    
    return it->second;
}

bool Scene::hasGameObject(const_str& name) {
    return (_gameObjects.find(name) == _gameObjects.end()) ? false : true;
}

GameObject& Scene::addGameObject(const GameObject::params& p) {
    assert(!p.name.empty() && !p.tag.empty());
    assert(_gameObjects.find(p.name) == _gameObjects.end());
    
    GameObject* gameObject = new GameObject(p);
    _gameObjects[p.name] = gameObject;
    
    return *gameObject;
}

void Scene::removeGameObject(const_str& name) {
    auto it = _gameObjects.find(name);
    
    assert(it != _gameObjects.end());
    
    for (auto& child : it->second->_children)
        removeGameObject(child->getName());
    
    _gameObjects.erase(it);
    delete it->second;
}
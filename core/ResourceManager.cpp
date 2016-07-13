//
//  ResourceManager.cpp
//  Flexo
//
//  Created by Ilya on 04/06/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#include "ResourceManager.hpp"

std::vector<ResourceManager*> ResourceManager::_resourceManagers;

ResourceManager::ResourceManager() {
    _resourceManagers.push_back(this);
}

void ResourceManager::freeResource(const_str& name) {
    auto it = _resources.find(name);
    assert(it != _resources.end());
   
    delete it->second;
    _resources.erase(it);
}

void ResourceManager::freeAll() {
    for (auto& resource : _resources)
        delete resource.second;
    _resources.clear();
}

const BaseResource& ResourceManager::getResource(const_str& name) const {
    auto it = _resources.find(name);
    assert(it != _resources.end());
    return *(it->second);
}

void ResourceManager::freeAllEver() {
    for (auto& resourceManager : _resourceManagers)
        resourceManager->freeAll();
}
//
//  Updater.cpp
//  Flexo
//
//  Created by Ilya on 27/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#include "Updater.hpp"
#include "core/Scene.hpp"
#include "GameObject.hpp"
#include "Component.hpp"

Updater& Updater::instance() {
    static Updater upd;
    return upd;
}

void Updater::update() {
    auto& gameObjects = Scene::getGameObjects();
    for (auto gm_it = gameObjects.begin(); gm_it != gameObjects.end(); ) {
        if (gm_it->second->isActive()) {
            auto components = gm_it->second->getComponents();
            for (auto cmp_it = components.begin(); cmp_it != components.end(); ) {
                cmp_it->second->update();
                cmp_it++;
            }
        }
        gm_it++;
    }
}

void Updater::awake() {
    for (auto& gm : Scene::getGameObjects()) {
        if (gm.second->isActive()) {
            auto gm_cmpnts = gm.second->getComponents();
            for (auto& cmp : gm_cmpnts) {
                if (cmp.second->isActive() && !isAwaked(cmp.second)) {
                    cmp.second->awake();
                    setAwaked(cmp.second, true);
                }
            }
        }
    }
}
/*
void Updater::setAwaked(Component* const c, bool flag) { c->_awaked = flag; }
bool Updater::isAwaked(Component* const c) const { return c->_awaked; } */
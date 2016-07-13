//
//  Component.cpp
//  Flexo
//
//  Created by Ilya on 25/05/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#include <assert.h>

#include "Component.hpp"
#include "Transform.hpp"

void Component::affectByTransform(Transform* transform, bool flag) {
    auto it = std::find(transform->_affectedBy.begin(), transform->_affectedBy.end(), this);
    
    if (flag) {
        assert(it == transform->_affectedBy.end());
        transform->_affectedBy.push_back(this);
    }
    else {
        assert(it != transform->_affectedBy.end());
        transform->_affectedBy.erase(it);
    }
}

void Updater::setAwaked(Component* const c, bool flag) { c->_awaked = flag; }
bool Updater::isAwaked(Component* const c) const { return c->_awaked; }
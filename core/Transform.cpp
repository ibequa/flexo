//
//  Transform.cpp
//  Flexo
//
//  Created by Ilya on 08/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include <cmath>

#include "Transform.hpp"
#include "GameObject.hpp"

const float Transform::DEG2RAD = M_PI / 180.0f;

Transform::Transform(const Component::params& params) : Component(params), _localScale(1.0f) {}

void Transform::translate(Transform& transform, const_vec3& by, Space space) {
    for (auto& child : transform.getGameObject()->getChildren())
        translate(*child->getTransform(), by, space);
    
    transform._translationMatrix.loadIdentity();
    
    switch (space) {
        case Space::WORLD: {
            transform._position += by;
            
            transform._translationMatrix(0, 3) = transform._position._x;
            transform._translationMatrix(1, 3) = transform._position._y;
            transform._translationMatrix(2, 3) = transform._position._z;
            break;
        }
        case Space::LOCAL: {
            fmath::vec3 localBy = transform._rotationMatrix * transform._scaleMatrix * by;
            transform._position += localBy;
            
            transform._translationMatrix(0, 3) = transform._position._x;
            transform._translationMatrix(1, 3) = transform._position._y;
            transform._translationMatrix(2, 3) = transform._position._z;
            break;
        }
    }
    
    for (auto& affectedComp : _affectedBy)
        affectedComp->translated(by);
}

void Transform::scale(Transform& transform, const_vec3& by) {
    for (auto& child : transform.getGameObject()->getChildren())
        scale(*child->getTransform(), by);
    
    transform._scaleMatrix(0, 0) *= by._x;
    transform._scaleMatrix(1, 1) *= by._y;
    transform._scaleMatrix(2, 2) *= by._z;
    
    transform._localScale *= by;
    
    for (auto& affectedComp : _affectedBy)
        affectedComp->scaled(by);
}

void Transform::setPosition(const_vec3& target) {
    _translationMatrix.loadIdentity();

    _translationMatrix(0, 3) = target._x;
    _translationMatrix(1, 3) = target._y;
    _translationMatrix(2, 3) = target._z;
    _position = target;
}

void Transform::setLocalScale(const_vec3& target) {
    _scaleMatrix(0, 0) *= target._x;
    _scaleMatrix(1, 1) *= target._y;
    _scaleMatrix(2, 2) *= target._z;
    _localScale = target;
}

void Transform::setLocalRotation(const_vec3& euler) {
    _localRotation = fmath::quaternion::fromEuler(euler);
    _rotationMatrix = fmath::quaternionToMatrix(_localRotation);
}

void Transform::rotateEuler(Transform& transform, const_vec3 euler, Space space) {
    
    for (auto& child : transform.getGameObject()->getChildren())
        rotateEuler(*child->getTransform(), euler, space);
    
    fmath::quaternion q = fmath::quaternion::fromEuler(euler);
    
    switch (space) {
        case Space::WORLD: {
            transform._localRotation = q * transform._localRotation;
            break;
        }
        case Space::LOCAL: {
            transform._localRotation *= q;
            break;
        }
    }
    transform._rotationMatrix = fmath::quaternionToMatrix(transform._localRotation);
    
    for (auto& affectedComp : _affectedBy)
        affectedComp->rotated(euler);
}
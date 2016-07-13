//
//  Camera.cpp
//  Flexo
//
//  Created by Ilya on 13/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include "Camera.hpp"
#include "RenderInfo.hpp"
#include "GameObject.hpp"

#include "Transform.hpp"

Camera::Camera(const Component::params& params) : Component(params) {
    _viewMatrix = fmath::lookAt(fmath::vec3::zero(), -fmath::vec3::forward(), fmath::vec3::up());
    
    renderInfo.CENGINE_MAT_V = &_viewMatrix;
    renderInfo.CENGINE_MAT_P = &_projectionMatrix;
}
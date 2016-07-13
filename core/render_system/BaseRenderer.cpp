//
//  BaseRenderer.cpp
//  Flexo
//
//  Created by Ilya on 14/05/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include <assert.h>
#include "BaseRenderer.hpp"

BaseRenderer::int_vec_bsrend_ptr BaseRenderer::_bsRendsPrioritized;

const BaseRenderer::int_vec_bsrend_ptr& BaseRenderer::getBaseRenderers() { return _bsRendsPrioritized; }

BaseRenderer::BaseRenderer(const Component::params& params, int drawPriority) : Component(params), _drawPriority(drawPriority) {
    _bsRendsPrioritized[drawPriority].push_back(this);
}

BaseRenderer::~BaseRenderer() {
    auto& vec = _bsRendsPrioritized[_drawPriority];
    auto it = std::find(vec.begin(), vec.end(), this);
    assert(it != vec.end());
    
    vec.erase(it);
}

void BaseRenderer::setDrawPriority(int value) {
    auto& vec = _bsRendsPrioritized[this->_drawPriority];
    auto it = std::find(vec.begin(), vec.end(), this);
    assert(it != vec.end());
    vec.erase(it);
    
    _bsRendsPrioritized[value].push_back(this);
    this->_drawPriority = value;
}
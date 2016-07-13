//
//  MeshRendererIndexed.cpp
//  Flexo
//
//  Created by Ilya on 24/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include <OpenGL/gl3.h>

#include "MeshRendererIndexed.hpp"
#include "BaseMaterial.hpp"

MeshRendererIndexed::MeshRendererIndexed(const Component::params& params, const MeshFilterIndexed& meshFilterIndexed, BaseMaterial& material, int drawPriority) :
BaseRenderer(params, drawPriority), _meshFilter(&meshFilterIndexed), _material(&material) {}

void MeshRendererIndexed::draw() const {
    _material->getShaderProgram().use();
    _material->activate();
    
    glBindVertexArray(_meshFilter->vao);
    glDrawElements(GL_TRIANGLES, _meshFilter->eboCount, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    _material->getShaderProgram().unuse();
}
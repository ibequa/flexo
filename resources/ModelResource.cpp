//
//  ModelResource.cpp
//  Flexo
//
//  Created by Ilya on 05/06/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#include "ModelResource.hpp"

Mesh& ModelResource::addMesh(const_str& name) {
    Mesh* mesh = new Mesh(name);
    _meshes.push_back(mesh);
    return *mesh;
}

ModelResource::ModelResource(const_str& path) : BaseResource(path) {}

ModelResource::~ModelResource() {
    for (auto& mesh : _meshes)
        delete mesh;
}
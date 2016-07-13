//
//  MeshFilterIndexed.hpp
//  Flexo
//
//  Created by Ilya on 14/05/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef MeshFilterIndexed_hpp
#define MeshFilterIndexed_hpp

#include <OpenGL/gl3.h>

#include "Component.hpp"
#include "Mesh.hpp"

class MeshFilterIndexed : public Component {
public:
    MeshFilterIndexed(const Component::params& params, const Mesh& mesh, GLenum usage);
    virtual ~MeshFilterIndexed();
    
    GLuint vbo, vao, ebo, eboCount, eboByteSize;
};

#endif /* MeshFilterIndexed_hpp */
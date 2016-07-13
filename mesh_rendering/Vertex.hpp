//
//  Vertex.hpp
//  Flexo
//
//  Created by Ilya on 06/06/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

struct Vertex {
    float position[3];
    float normal[3];
    float tangent[3];
    float bitangent[3];
    float uv[2];
};

#endif /* Vertex_hpp */
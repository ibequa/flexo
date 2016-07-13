//
//  Mesh.hpp
//  Flexo
//
//  Created by Ilya on 24/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <vector>
#include <string>

#include "Vertex.hpp"

class Mesh {
    typedef const std::string const_str;
    typedef std::vector<Vertex> vec_vertex;
    typedef std::vector<unsigned int> vec_uint;
private:
    const_str _name;
    
    vec_vertex _vertices;
    vec_uint _indices;
    
public:
    Mesh(const_str& name) : _name(name) {}
    virtual ~Mesh() {}
    
    inline void addVertex(const Vertex& v) { _vertices.push_back(v); }
    inline void addIndex(unsigned int index) { _indices.push_back(index); }
    
    inline const_str& getName() const { return _name; }
    inline const vec_vertex& getVerticies() const { return _vertices; }
    inline const vec_uint& getIndices() const { return _indices; }
};


#endif /* Mesh_hpp */
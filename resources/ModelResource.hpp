//
//  ModelResource.hpp
//  Flexo
//
//  Created by Ilya on 31/05/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#ifndef ModelResource_hpp
#define ModelResource_hpp

#include <vector>

#include "BaseResource.hpp"
#include "Mesh.hpp"

class ModelResource final : public BaseResource {
    typedef const std::string const_str;
private:
    std::vector<Mesh*> _meshes;
    
public:
    ModelResource(const_str& name);
    ~ModelResource();
    
    Mesh& addMesh(const_str& name);
    
    inline const std::vector<Mesh*>& getMeshes() const { return _meshes; }
};

#endif /* ModelResource_hpp */
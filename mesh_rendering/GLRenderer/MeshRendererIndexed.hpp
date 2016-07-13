//
//  MeshRendererIndexed.hpp
//  Flexo
//
//  Created by Ilya on 24/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef MeshRenderer_hpp
#define MeshRenderer_hpp

#include "BaseRenderer.hpp"
#include "MeshFilterIndexed.hpp"

class BaseMaterial;

class MeshRendererIndexed final : public BaseRenderer {
private:
    BaseMaterial* _material = nullptr;
    const MeshFilterIndexed* _meshFilter = nullptr;
    
public:
    MeshRendererIndexed(const Component::params&, const MeshFilterIndexed& meshFilter, BaseMaterial& material, int drawPriority);
    
    void draw() const;
    
    inline BaseMaterial& getMaterial() const { return *_material; }
    inline void setMaterial(BaseMaterial& material) { _material = &material; }
};

#endif /* MeshRendererIndexed_hpp */
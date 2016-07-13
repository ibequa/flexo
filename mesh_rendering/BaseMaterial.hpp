//
//  BaseMaterial.hpp
//  Flexo
//
//  Created by Ilya on 24/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef BaseMaterial_hpp
#define BaseMaterial_hpp

#include <string>
#include "GLProgram.hpp"
#include "Component.hpp"

class Mesh;

class BaseMaterial : public Component {
    friend class Mesh;
    
    typedef const std::string const_str;
public:
    struct params {
        params() = default;
        params(const Mesh& mesh_, const GLProgram& shaderProgram_) : mesh(&mesh_), shaderProgram(&shaderProgram_) {}
        
        const Mesh* mesh;
        const GLProgram* shaderProgram;
    };
    
    virtual void activate() const = 0;
    
    inline const GLProgram& getShaderProgram() const { return *_initParams.shaderProgram; }
    inline void setShaderProgram(const GLProgram& shaderProgram) { _initParams.shaderProgram = &shaderProgram; }

protected:
    BaseMaterial(const Component::params& cparams, const BaseMaterial::params& mparams) : Component(cparams), _initParams(mparams) {}
    virtual ~BaseMaterial() {}
    
    inline const Mesh& getMesh() const { return *_initParams.mesh; }
    
private:
    BaseMaterial::params _initParams;
};

#endif /* BaseMaterial_hpp */
//
//  ModelAssembler.hpp
//  Flexo
//
//  Created by Ilya on 24/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef ModelAssembler_hpp
#define ModelAssembler_hpp

#include "Component.hpp"
#include "GLProgram.hpp"
#include "ModelResource.hpp"

class ModelAssembler final : public Component {
    typedef const std::string const_str;
public:
    ModelAssembler(const Component::params&, const ModelResource& model, const GLProgram& shaderProgram, int drawPriority = 1);
};

#endif /* ModelRenderer_hpp */
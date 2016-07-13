//
//  ModelAssembler.cpp
//  Flexo
//
//  Created by Ilya on 09/06/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#include "ModelAssembler.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include "MeshFilterIndexed.hpp"
#include "MeshRendererIndexed.hpp"
#include "DefaultMaterial.hpp"

ModelAssembler::ModelAssembler(const Component::params& cparams, const ModelResource& model, const GLProgram& shaderProgram, int drawPriority) : Component(cparams) {
    
    const auto& path = model.path;
    
    /// get model name from path
    size_t last_slash = path.find_last_of("/");
    size_t dot = (path.size() - path.find_last_of(".") + 1);
    std::string modelName = path.substr((last_slash == std::string::npos) ? 0 : last_slash, path.size() - last_slash - dot);
    ///
    
    std::string uniqueName;
    for (size_t i = 0; i < model.getMeshes().size(); i++) {
        auto& meshes = model.getMeshes();
        uniqueName = meshes[i]->getName();
        if (uniqueName.empty())
            uniqueName = modelName + std::to_string(i);
        else
            uniqueName += std::to_string(i);
        
        GameObject& g = Scene::addGameObject(uniqueName);
        MeshFilterIndexed& filter = g.addComponent<MeshFilterIndexed>({"MeshFilterIndexed", &g}, *meshes[i], GL_STATIC_DRAW);
        
        BaseMaterial& material = (BaseMaterial&) g.addComponent<DefaultMaterial>({"DefaultMaterial", &g}, BaseMaterial::params(*meshes[i], shaderProgram));
        g.addComponent<MeshRendererIndexed>({"MeshRendererIndexed", &g}, filter, material, drawPriority);
        
        cparams.gameObject->addChild(g);
    }
}
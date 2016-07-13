//
//  ModelImporter.hpp
//  Flexo
//
//  Created by Ilya on 06/05/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef ModelImporter_hpp
#define ModelImporter_hpp

#include <string>
#include <assimp/scene.h>

#include "BaseImporter.hpp"
#include "ModelResource.hpp"

class Mesh;

class ModelImporter : public BaseImporter<ModelResource> {
    typedef const std::string const_str;
private:
    ModelImporter() {}
    
    void processMesh(const aiMesh* meshAi, Mesh& mesh, const aiScene* scene);
    void processNode(const aiNode* node, const aiScene* scene, ModelResource& model);
    
public:
    static ModelImporter& instance();
    
    const ModelResource& import(const_str& path);
};

#endif /* ModelImporter_hpp */
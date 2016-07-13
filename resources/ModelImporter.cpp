//
//  ModelImporter.cpp
//  Flexo
//
//  Created by Ilya on 06/05/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include <assert.h>
#include <OpenGL/gltypes.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "ModelImporter.hpp"
#include "MaterialInfoImported.hpp"
#include "DefaultMaterial.hpp"

#define copy_v_attr3(v_attr, aiV_attr)   v.v_attr[0] = meshAi->aiV_attr[i].x; \
                                        v.v_attr[1] = meshAi->aiV_attr[i].y; \
                                        v.v_attr[2] = meshAi->aiV_attr[i].z

#define get_ai_prop(key, out) scene->mMaterials[mat_id]->Get(key, out)

#define ai2arr(ai, a) mesh->_materialInfoImported_->a[0] = ai.r; \
                        mesh->_materialInfoImported_->a[1] = ai.g; \
                        mesh->_materialInfoImported_->a[2] = ai.b

ModelImporter& ModelImporter::instance() {
    static ModelImporter _modelImporter;
    return _modelImporter;
}

const ModelResource& ModelImporter::import(const_str& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes);
    assert (scene && (scene->mFlags != AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode);
    
    ModelResource& model = addResource(path);
    
    processNode(scene->mRootNode, scene, model);
    
    return model;
}

void ModelImporter::processNode(const aiNode* node, const aiScene* scene, ModelResource& model) {
    for (size_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh* meshAi = scene->mMeshes[node->mMeshes[i]];
        
        Mesh& mesh = model.addMesh(meshAi->mName.C_Str());
        
        processMesh(meshAi, mesh, scene);
    }
    
    for (GLuint i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene, model);
}

void ModelImporter::processMesh(const aiMesh* meshAi, Mesh& mesh, const aiScene* scene) {
    // VERTEX DATA
    for (GLuint i = 0; i < meshAi->mNumVertices; i++) {
        Vertex v;
        copy_v_attr3(position, mVertices);
        
        copy_v_attr3(normal, mNormals);
        
        if (meshAi->HasTextureCoords(0)) {
            v.uv[0] = meshAi->mTextureCoords[0][i].x;
            v.uv[1] = meshAi->mTextureCoords[0][i].y;
        }
        
        if (meshAi->HasTangentsAndBitangents()) {
            copy_v_attr3(tangent, mTangents);
            copy_v_attr3(bitangent, mBitangents);
        }
        
        mesh.addVertex(v);
    }
    //
    // INDICES
    for (GLuint i = 0; i < meshAi->mNumFaces; i++) {
        aiFace face = meshAi->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++)
            mesh.addIndex(face.mIndices[j]);
    }
    //
    // MATERIALS
    // import colors and textures and pass to default material: addMaterial(DefaultMaterial, "vertsh", "fragsh", imported stuff)
    /*unsigned int mat_id = meshAi->mMaterialIndex;
    if (mat_id > 0) {
        mesh->_materialInfoImported_ = new MaterialInfoImported;
        
        aiColor3D aiAmbient, aiDiffuse, aiSpecular, aiEmission, aiTransparent;
        get_ai_prop(AI_MATKEY_COLOR_AMBIENT, aiAmbient);
        get_ai_prop(AI_MATKEY_COLOR_DIFFUSE, aiDiffuse);
        get_ai_prop(AI_MATKEY_COLOR_SPECULAR, aiSpecular);
        get_ai_prop(AI_MATKEY_COLOR_EMISSIVE, aiEmission);
        get_ai_prop(AI_MATKEY_COLOR_TRANSPARENT, aiTransparent);
        get_ai_prop(AI_MATKEY_SHININESS, mesh->_materialInfoImported_->shininess);
        get_ai_prop(AI_MATKEY_SHININESS_STRENGTH, mesh->_materialInfoImported_->shininessStrength);
        
        ai2arr(aiAmbient, ambient); ai2arr(aiDiffuse, diffuse); ai2arr(aiSpecular, specular);
        ai2arr(aiTransparent, transparent); ai2arr(aiEmission, emission);
    } */
    //
}
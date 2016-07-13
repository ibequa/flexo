//
//  DefaultMaterial.cpp
//  Flexo
//
//  Created by Ilya on 30/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include <OpenGL/gl3.h>
#include "DefaultMaterial.hpp"
#include "RenderInfo.hpp"
#include "TextureImporter.hpp"

DefaultMaterial::DefaultMaterial(const Component::params& cparams, const BaseMaterial::params& params) : BaseMaterial(cparams, params) {
   // TextureResource& tex = (TextureResource&) TextureImporter::instance().resourceManager.getResource("wall.jpg");
    
//glGenTextures(1, &texID);
  //  glBindTexture(GL_TEXTURE_2D, texID);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  //  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.w, tex.h, 0, GL_BGRA, GL_UNSIGNED_BYTE, tex.getPixels());
  //  glGenerateMipmap(GL_TEXTURE_2D);
  //  glBindTexture(GL_TEXTURE_2D, 0);
}

void DefaultMaterial::activate() const {
//    GLuint modelLoc = glGetUniformLocation(_shaders_->_programID, "mat_m");
 //   GLuint viewLoc = glGetUniformLocation(_shaders_->_programID, "mat_v");
   // GLuint projLoc = glGetUniformLocation(_shaders_->_programID, "mat_p");
    GLuint normalLoc = glGetUniformLocation(getShaderProgram().getID(), "mat_normal");
    GLuint mvpLoc = glGetUniformLocation(getShaderProgram().getID(), "mat_mvp");
    
 //   glBindTexture(GL_TEXTURE_2D, texID);
    
   // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, renderInfo._CENGINE_MAT_M->rawData());
   // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, renderInfo._CENGINE_MAT_V->rawData());
   // glUniformMatrix4fv(projLoc, 1, GL_FALSE, renderInfo._CENGINE_MAT_P->rawData());
    glUniformMatrix4fv(normalLoc, 1, GL_FALSE, renderInfo.CENGINE_MAT_NORMAL->rawData());
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, renderInfo.CENGINE_MAT_MVP->rawData());
}
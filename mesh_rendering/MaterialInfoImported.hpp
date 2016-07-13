//
//  MaterialInfoImported.hpp
//  Flexo
//
//  Created by Ilya on 30/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef MaterialInfoImported_hpp
#define MaterialInfoImported_hpp

#include <OpenGL/gltypes.h>
#include <string>

struct MaterialInfoImported {
    float ambient[3];
    float diffuse[3];
    float specular[3];
    float transparent[3];
    float emission[3];
    float shininess;
    float shininessStrength;
    
    GLuint ambient_tex;            // map_Ka
    GLuint diffuse_tex;            // map_Kd
    GLuint specular_tex;           // map_Ks
    GLuint specular_highlight_tex; // map_Ns
    GLuint bump_tex;               // map_bump, bump
    GLuint displacement_tex;       // disp
    GLuint alpha_tex;              // map_d
};

#endif /* MaterialInfoImported_hpp */
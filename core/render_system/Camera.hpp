//
//  Camera.hpp
//  Flexo
//
//  Created by Ilya on 13/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "fmath/fmath.hpp"
#include "Transform.hpp"
#include "GameObject.hpp"

#include <cmath>

#define DEG2RAD(x) (x * M_PI / 180.0f)

class Camera final : public Component {
    typedef const fmath::vec3 const_vec3;
   
public:
    Camera(const Component::params&);
    
    fmath::mat4 _projectionMatrix, _viewMatrix;
    
#warning test
    inline void setOrtho(int width, int height, float n, float f) {
        float w2 = (float) width / 2.0f;
        float h2 = (float) height / 2.0f;
        _projectionMatrix = fmath::ortho(-w2, w2, -h2, h2, n, f);
    }
    
    inline void setPerspective(float fovy, float aspect, float n, float f) {
        _projectionMatrix = fmath::perspective(fovy, aspect, n, f);
    }
    
    inline void translated(const_vec3& by) {
        fmath::mat4 trMatrix;
        trMatrix = fmath::translate(trMatrix, -by);
        _viewMatrix = trMatrix * _viewMatrix;
    }
    
    inline void rotated(const_vec3& euler) {
        
    }
    
    inline void scaled(const_vec3& by) {}
    
  //  inline void lookAt(fmath::vec3 at) { _viewMatrix = fmath::lookAt(_position, at, fmath::vec3(0.0f, 1.0f, 0.0f)); }
};

#endif /* Camera_hpp */
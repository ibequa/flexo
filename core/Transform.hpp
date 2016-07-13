//
//  Transform.hpp
//  Flexo
//
//  Created by Ilya on 08/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <vector>

#include "fmath/fmath.hpp"
#include "Component.hpp"

enum Space { LOCAL, WORLD };

class Transform final : public Component {
    typedef const fmath::vec3 const_vec3;
    typedef const fmath::quaternion const_quaternion;
    
private:
    fmath::vec3 _position, _localScale;
    fmath::quaternion _localRotation;
    
    std::vector<Component*> _affectedBy;
    
    void translate(Transform&, const_vec3&, Space space);
    void scale(Transform&, const_vec3&);
    void rotateEuler(Transform&, const_vec3, Space space);
    
public:
    static const float DEG2RAD;
    
    Transform(const Component::params& params);
    
    friend void Component::affectByTransform(Transform* transform, bool flag);
    
    fmath::mat4 _translationMatrix, _rotationMatrix, _scaleMatrix;
    
    // these 3 matrices are updated per frame
    fmath::mat4 _modelMatrix;
    fmath::mat4 _mvpMatrix;
    fmath::mat4 _normalMatrix;    // (_modelMatrix^(-1))^T
    
    inline const std::vector<Component*>& getAffectedComponents() { return _affectedBy; }
    inline const_vec3& getPosition() const { return _position; }
    inline const_vec3& getLocalScale() const { return _localScale; }
    inline const_quaternion& getLocalRotation() const { return _localRotation; }
    
    void setPosition(const_vec3& target);
    void setLocalScale(const_vec3& target);
    void setLocalRotation(const_vec3& euler);
    
    inline void translate(const_vec3& by, Space space = Space::WORLD) { if (isActive()) translate(*this, by, space); }
    inline void scale(const_vec3& by) { if (isActive()) scale(*this, by); }
    inline void rotateEuler(const_vec3& euler, Space space = Space::WORLD) { if (isActive()) rotateEuler(*this, euler, space); }
};

#endif /* Transform_hpp */
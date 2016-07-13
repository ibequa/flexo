//
//  Component.hpp
//  Flexo
//
//  Created by Ilya on 08/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <string>

#include "vec3.hpp"
#include "Updater.hpp"

class GameObject;
class Transform;

class Component {
    friend class GameObject;
    
    typedef const fmath::vec3 const_vec3;
    typedef const std::string const_str;
    
public:
    struct params {
        params(const_str& name_, GameObject* gameObject_, bool active_ = 1) : name(name_), active(active_), gameObject(gameObject_) {}
        
        std::string name;
        bool active;
        GameObject* gameObject;
    };
   
    virtual void awake() {}
    virtual void update() {}
    
    virtual void translated(const_vec3& by) {}
    virtual void scaled(const_vec3& by) {}
    virtual void rotated(const_vec3& euler) {}
    
    inline const_str& getName() const { return _initParams.name; }
    inline GameObject* getGameObject() const { return _initParams.gameObject; }
    inline bool isActive() const { return _initParams.active; }
    inline void setActive(bool flag) { _initParams.active = flag; }
    
    friend void Updater::setAwaked(Component* const c, bool flag);
    friend bool Updater::isAwaked(Component* const c) const;
    
    void affectByTransform(Transform* transform, bool flag);
    
protected:
    Component(const params& initParams) : _initParams(initParams) {}
    virtual ~Component() {}
 
private:
    void* operator new (std::size_t sz) { return ::operator new(sz); }
    void* operator new[] (std::size_t sz) { return ::operator new[](sz); }
    
    params _initParams;
    bool _awaked = false;
};

#endif /* Component_hpp */
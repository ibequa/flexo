//
//  GameObject.hpp
//  Flexo
//
//  Created by Ilya on 08/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <assert.h>
#include <string>
#include <map>
#include <vector>

#include "Component.hpp"

class Transform;

class GameObject {
    friend class Scene;
    
    typedef std::map<std::string, Component*> str_compptr_map;
    typedef const std::string const_str;
    
public:
    struct params {
        params(const_str& name_, const_str& tag_ = "Default", bool active_ = 1, bool persistent_ = 0) : name(name_), tag(tag_), active(active_), persistent(persistent_) {}
        
        std::string name;
        std::string tag;
        bool persistent;
        bool active;
    };
    
    inline const_str& getName() const { return _initParams.name; }
    inline const_str& getTag() const { return _initParams.tag; }
    inline const std::vector<GameObject*>& getChildren() const { return _children; }
    inline const str_compptr_map& getComponents() const { return _components; }
    inline Transform* getTransform() const { return _transform; }
    inline GameObject* getParent() const { return _parent; }
    inline bool isActive() const { return _initParams.active; }
    inline bool isPersistent() const { return _initParams.persistent; }
    bool hasComponent(const_str& name) const;
    
    bool hasChild(const_str& name) const;
    inline bool hasChildRecursively(const_str& name) const { return hasChildRecursively_(*this, name); }
    
    inline void setActive(bool flag) { _initParams.active = flag; }
    inline void setPersistent(bool flag) { _initParams.persistent = flag; }
    
    inline void addChild(GameObject& child) { addChild_(*this, child); }
    // moves the child up to the parent of from
    inline void detachChild(GameObject& child) { detachChild_(*this, child); }
    // moves the child all the way up
    inline void detachChildRecursively(GameObject& child) { detachChildRecursively_(*this, child); }
    
    // a child of a parent's child is not a parent's child (relationship is not transistive)
    GameObject* findChild(const_str& name) const;
    GameObject* findChildRecursively(GameObject& from, const_str& name) const;
    
    template <typename T, typename... Args>
    T& addComponent(const Component::params& initParams, Args&&... args);
    
    Component* findComponent(const_str& name) const;
    
    void removeComponent(const_str& name);
    
protected:
    GameObject(const params&);
    virtual ~GameObject();
    
private:
    params _initParams;
    
    Transform* _transform;
    
    str_compptr_map _components;
    
    std::vector<GameObject*> _children;
    GameObject* _parent = nullptr;
    
    friend void addChild_(GameObject& parent, GameObject& child);
    friend void detachChild_(GameObject& from, GameObject& child);
    friend void detachChildRecursively_(GameObject& parent, GameObject& child);
    friend bool hasChildRecursively_(const GameObject& parent, const_str& name);
};

template <typename T, typename... Args>
T& GameObject::addComponent(const Component::params& initParams, Args&&... args) {
    assert(_components.find(initParams.name) == _components.end());
    
    T *comp = new T(initParams, std::forward<Args>(args)...);
    
    assert(dynamic_cast<T*>(comp));
    _components[initParams.name] = comp;
    
    return *comp;
}

#endif /* GameObject_hpp */
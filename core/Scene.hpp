//
//  Scene.hpp
//  Flexo
//
//  Created by Ilya on 12/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <assert.h>
#include <string>
#include <vector>
#include <map>

#include "GameObject.hpp"

#define SCENE_CTOR_CPP(class) class(const std::string& name, int id) : Scene(name, id)
#define SCENE_CTOR_H(class) class(const std::string& name, int id)

class Scene {
    friend class SceneManager;
    
    typedef std::map<std::string, GameObject*> str_gameobjptr_map;
    typedef const std::string const_str;
    
private:
    static str_gameobjptr_map _gameObjects;
    
    const_str _name;
    const int _id;
    
protected:
    Scene(const_str& name, int id);
    virtual ~Scene();
    
public:
    template <typename T, typename... Args>
    static T& addGameObject(const GameObject::params& p, Args&&... args) {
        assert(!p.name.empty() && !p.tag.empty());
        assert(_gameObjects.find(p.name) == _gameObjects.end());
        
        T* gameObject = new T(p, std::forward<Args>(args)...);
        
        assert(dynamic_cast<GameObject*>(gameObject));
        _gameObjects[p.name] = gameObject;
        
        return *gameObject;
    }
    
    static GameObject& addGameObject(const GameObject::params&);
    // removes also all its children
    static void removeGameObject(const_str& name);
    static GameObject* findGameObject(const_str& name);
    
    static bool hasGameObject(const_str& name);
    
    static const str_gameobjptr_map& getGameObjects() { return _gameObjects; }
};

#endif /* Scene_hpp */
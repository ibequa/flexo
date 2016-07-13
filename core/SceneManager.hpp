//
//  SceneManager.hpp
//  Flexo
//
//  Created by Ilya on 12/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <string>

#include "Scene.hpp"

class SceneManager final {
    typedef const std::string const_str;
    
private:
    SceneManager() : _currentScene(nullptr) {}
    
    Scene* _currentScene;
    
public:
    static SceneManager& instance();
    
    template <typename T>
    void initScene(const_str& name, int id);
    
    void loadQuit();
    
    int getCurrentSceneID() const { return _currentScene->_id; }
    const_str& getCurrentSceneName() const { return _currentScene->_name; }
};

template <typename T>
void SceneManager::initScene(const_str& name, int id) {
    delete _currentScene;
    
    Scene* newScene = new T(name, id);
    
    _currentScene = newScene;
}

#endif /* SceneManager_hpp */
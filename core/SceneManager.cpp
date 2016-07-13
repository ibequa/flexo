//
//  SceneManager.cpp
//  Flexo
//
//  Created by Ilya on 12/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#include "SceneManager.hpp"

SceneManager& SceneManager::instance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::loadQuit() {
    delete _currentScene;
    _currentScene = nullptr;
}
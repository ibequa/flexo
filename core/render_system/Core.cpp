//
//  Core.cpp
//  Flexo
//
//  Created by Ilya on 24/02/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#include <SDL2/SDL_timer.h>
#include "Core.hpp"
#include "Time.hpp"
#include "Updater.hpp"
#include "Renderer.hpp"
#include "Inputer.hpp"

Core::Core(int w, int h, int targetFPS, bool fullScreenMode, const std::string& title) {
    Renderer::instantiate(w, h, targetFPS, fullScreenMode, title);
}

void Core::gameloop() {
    int frameTime = 1000 / renderer->_targetFPS;
    int currentTime = SDL_GetTicks();
    
    int previousFrameTime, newTime;
    
    Time::_deltaTime = frameTime;
    
    while (!Inputer::isQuitRequested()) {
        
        updater.awake();
    
        Inputer::processInput();
        
        updater.update();
        
        Inputer::reset();
        
        renderer->render();
        
        newTime = SDL_GetTicks();
        previousFrameTime = newTime - currentTime;
        currentTime = newTime;
        
        Time::_deltaTime = previousFrameTime;
        
        if (previousFrameTime < frameTime)
            SDL_Delay(frameTime - previousFrameTime);
        
    }
}
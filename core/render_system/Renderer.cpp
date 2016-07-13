//
//  Renderer.cpp
//  Flexo
//
//  Created by Ilya on 15/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#include <OpenGL/gl3.h>
#include <SDL2/sdl.h>
#include <assert.h>

#include "Renderer.hpp"

#include "BaseRenderer.hpp"
#include "GameObject.hpp"
#include "RenderInfo.hpp"
#include "Transform.hpp"

Renderer* Renderer::_renderer = nullptr;

Renderer::Renderer(int w, int h, int targetFPS, bool fullScreenMode, const std::string &title) : _targetFPS(targetFPS), _fullScreenMode(fullScreenMode), _title(title), _w(w), _h(h) {
    _renderer = this;
    assert(w > 0 && h > 0 && targetFPS > 0);
    setup();
}

Renderer& Renderer::instantiate(int w, int h, int targetFPS, bool fullScreenMode, const std::string& title) {
    static Renderer rend(w, h, targetFPS, fullScreenMode, title);
    return rend;
}

void Renderer::drawObjects() {
    for (auto& bsRendPriorityBatch : BaseRenderer::getBaseRenderers()) {
        for (auto& bsRend : bsRendPriorityBatch.second) {
            if (!bsRend->isActive() || !bsRend->getGameObject()->isActive())
                continue;
            
            ////SETUP RENDER INFO////
#warning encapsulate render info setup; update only per gameobject
            Transform& transform = *bsRend->getGameObject()->getTransform();
            transform._modelMatrix = transform._translationMatrix * transform._rotationMatrix * transform._scaleMatrix;
            renderInfo.CENGINE_MAT_M = &transform._modelMatrix;
            
            transform._mvpMatrix = (*(renderInfo.CENGINE_MAT_P) * (*(renderInfo.CENGINE_MAT_V) * *(renderInfo.CENGINE_MAT_M)));
            renderInfo.CENGINE_MAT_MVP = &transform._mvpMatrix;
            
            bsRend->getGameObject()->getTransform()->_normalMatrix = transform._modelMatrix.inversed().transposed();
            renderInfo.CENGINE_MAT_NORMAL = &transform._normalMatrix;
            /////////////////////////
            
            bsRend->draw();
        }
    }
}

void Renderer::preDrawObjects() {
    for (auto& bsRendPriorityBatch : BaseRenderer::getBaseRenderers()) {
        for (auto& bsRend : bsRendPriorityBatch.second) {
            if (!bsRend->isActive() || !bsRend->getGameObject()->isActive())
                continue;
            bsRend->preDrawAll();
        }
    }
}

void Renderer::preSwapWindow() {
    for (auto& bsRendPriorityBatch : BaseRenderer::getBaseRenderers()) {
        for (auto& bsRend : bsRendPriorityBatch.second) {
            if (!bsRend->isActive() || !bsRend->getGameObject()->isActive())
                continue;
            bsRend->preSwapBuffers();
        }
    }
}

void Renderer::setup() {
    SDL_Init(SDL_INIT_EVERYTHING);
        
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_Rect rect;
    SDL_GetDisplayBounds(0, &rect);
    _displayWidth = rect.w;
    _displayHeight = rect.h;
    
    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               _w, _h, SDL_WINDOW_OPENGL);
    assert(_window != nullptr);
    
    if (_fullScreenMode) {
        SDL_SetWindowSize(_window, _displayWidth, _displayHeight);
        _w = _displayWidth;
        _h = _displayHeight;
        SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    assert(glContext != nullptr);
    
    glViewport(0, 0, _w, _h);
    
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0, 0, 0, 1);
    
    printVersions();
    
    //SDL_GL_SetSwapInterval(0); // vsync off
    
    atexit(SDL_Quit);
}

void Renderer::printVersions() {
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void Renderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    preDrawObjects();
    drawObjects();
    preSwapWindow();
    SDL_GL_SwapWindow(_window);
}
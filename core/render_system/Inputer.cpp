//
//  Inputer.cpp
//  Flexo
//
//  Created by Ilya on 11/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include "Inputer.hpp"
#include <SDL2/SDL_events.h>

#define find(in, el) std::find(in.begin(), in.end(), el)
#define exists(in, el) find(in, el) != in.end()

bool Inputer::_running = true;
std::vector<SDL_Keycode> Inputer::_downKeys;
std::vector<SDL_Keycode> Inputer::_upKeys;
std::vector<SDL_Keycode> Inputer::_pressedKeys;

void Inputer::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        SDL_Keycode key = event.key.keysym.sym;
        switch(event.type) {
            case SDL_QUIT:
                _running = false;
                break;
            case SDL_KEYDOWN:
                if (!(exists(_pressedKeys, key))) {
                    _downKeys.push_back(key);
                    _pressedKeys.push_back(key);
                }
                break;
            case SDL_KEYUP:
                _upKeys.push_back(key);
                _pressedKeys.erase(find(_pressedKeys, key));
                break;
        }
    }
}

void Inputer::reset() { _upKeys.clear(); _downKeys.clear(); }

bool Inputer::getKey(SDL_Keycode key) {
    return exists(_pressedKeys, key) ? true : false;
}

bool Inputer::getKeyUp(SDL_Keycode key) {
    return exists(_upKeys, key) ? true : false;
}

bool Inputer::getKeyDown(SDL_Keycode key) {
    return exists(_downKeys, key) ? true : false;
}
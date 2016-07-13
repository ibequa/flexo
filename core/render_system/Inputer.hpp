//
//  Inputer.hpp
//  Flexo
//
//  Created by Ilya on 13/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#ifndef Inputer_hpp
#define Inputer_hpp

#include <SDL2/SDL_keycode.h>
#include <vector>

#include "Core.hpp"

class Inputer final {
    friend class Core;
private:
    static bool _running;
    static std::vector<SDL_Keycode> _downKeys;
    static std::vector<SDL_Keycode> _upKeys;
    static std::vector<SDL_Keycode> _pressedKeys;
    
    static void processInput();
    static void reset();
    
public:
    inline static bool isQuitRequested() { return !_running; }
    
    static bool getKey(SDL_Keycode);
    static bool getKeyUp(SDL_Keycode);
    static bool getKeyDown(SDL_Keycode);
};

#endif /* Inputer_hpp */
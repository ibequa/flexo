//
//  Renderer.hpp
//  Flexo
//
//  Created by Ilya on 13/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <string>
#include <SDL2/SDL_video.h>

#define renderer Renderer::_renderer

class Renderer final {
    friend class Core;
    
private:
    SDL_Window* _window;
    
    int _w, _h;
    int _displayWidth, _displayHeight;
    bool _fullScreenMode;
    
    const int _targetFPS;
    const std::string _title;
    
    Renderer(int w, int h, int targetFPS, bool fullScreenMode, const std::string& title);
   
    static Renderer& instantiate(int w, int h, int targetFPS, bool fullScreenMode, const std::string& title);
    
    void setup();
    
    // TODO: these must be const-qualified
    void drawObjects();
    void preDrawObjects();
    void preSwapWindow();
    
    void render();
    void printVersions();
    
public:
    inline int getWindowW() const { return _w; }
    inline int getWindowH() const { return _h; }
    inline int getDisplayW() const { return  _displayWidth; }
    inline int getDisplayH() const { return _displayHeight; }
    
    inline int getTargetFPS() const { return _targetFPS; }
    inline const std::string& getTitle() const { return _title; }
    
    static Renderer* _renderer;
};

#endif /* Renderer_hpp */
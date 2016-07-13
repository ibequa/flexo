//
//  TextureImporter.cpp
//  Flexo
//
//  Created by Ilya on 07/05/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include <assert.h>
#include <SDL2_image/SDL_image.h>

#include "TextureImporter.hpp"

TextureImporter& TextureImporter::instance() {
    static TextureImporter _textureImporter;
    return _textureImporter;
}

const TextureResource& TextureImporter::import(const_str& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    assert(surface && IMG_GetError());
    
    TextureResource& texture = addResource(path, surface->w, surface->h, surface->format->BytesPerPixel, (unsigned int*) (surface->pixels));
    
    SDL_FreeSurface(surface);
    
    return texture;
}
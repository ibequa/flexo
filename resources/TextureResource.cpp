//
//  TextureResource.cpp
//  Flexo
//
//  Created by Ilya on 05/06/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#include <cstring>

#include "TextureResource.hpp"

TextureResource::TextureResource(const std::string& path, int w, int h, int bytesPerPixel, const uint* pixelData) : BaseResource(path), _w(w), _h(h), _bytesPerPixel(bytesPerPixel) {
    surfaceSize = w * h * bytesPerPixel;
    
    _pixels = new uint[surfaceSize];
    memcpy(_pixels, pixelData, surfaceSize);
}

TextureResource::~TextureResource() {
    delete [] _pixels;
}
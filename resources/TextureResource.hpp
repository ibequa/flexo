//
//  TextureResource.hpp
//  Flexo
//
//  Created by Ilya on 31/05/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#ifndef TextureResource_hpp
#define TextureResource_hpp

#include <string>

#include "BaseResource.hpp"

struct TextureResource final : public BaseResource {
    typedef unsigned int uint;
private:
    uint* _pixels;
    uint surfaceSize;
    
    const int _w;
    const int _h;
    const int _bytesPerPixel;
    
public:
    inline const int getWidth() const { return _w; }
    inline const int getHeight() const { return _h; }
    inline const int getBytesPerPixel() const { return _bytesPerPixel; }
    inline const uint* getPixels() const { return _pixels; }
    
    TextureResource(const std::string& path, int w, int h, int bytesPerPixel, const uint* pixelData);
    ~TextureResource();
};

#endif /* TextureResource_hpp */

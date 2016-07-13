//
//  TextureImporter.hpp
//  Flexo
//
//  Created by Ilya on 07/05/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef TextureImporter_hpp
#define TextureImporter_hpp

#include <string>

#include "BaseImporter.hpp"
#include "TextureResource.hpp"

class TextureImporter : public BaseImporter<TextureResource> {
    typedef const std::string const_str;
private:
    TextureImporter() {}
    
public:
    static TextureImporter& instance();
    
    const TextureResource& import(const_str& path);
};

#endif /* TextureImporter_hpp */
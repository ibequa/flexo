//
//  BaseResource.hpp
//  Flexo
//
//  Created by Ilya on 01/06/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#ifndef BaseResource_hpp
#define BaseResource_hpp

#include <string>

struct BaseResource {
    const std::string path;
    
    BaseResource(const std::string& _path) : path(_path) {}
    virtual ~BaseResource() {}
};

#endif /* BaseResource_hpp */

//
//  ResourceManager.hpp
//  Flexo
//
//  Created by Ilya on 01/06/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <unordered_map>
#include <string>
#include <vector>
#include <assert.h>

#include "BaseResource.hpp"

class ResourceManager final {
    typedef const std::string const_str;
    typedef std::unordered_map<std::string, BaseResource*> str_baseresptr_map;
private:
    str_baseresptr_map _resources;
    
    static std::vector<ResourceManager*> _resourceManagers;
    
public:
    ResourceManager();
    
    template <typename T, typename... Args>
    T& addResource(const_str& name, Args&&... args) {
        assert(_resources.find(name) == _resources.end());
        
        T* resource = new T(name, std::forward<Args>(args)...);
        
        assert(dynamic_cast<BaseResource*>(resource));
        _resources[name] = resource;
        return *resource;
    }
    
    void freeResource(const_str& name);
    void freeAll();
    const BaseResource& getResource(const_str& name) const;
    
    static void freeAllEver();
};

#endif /* ResourceManager_hpp */
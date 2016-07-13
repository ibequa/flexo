//
//  BaseImporter.hpp
//  Flexo
//
//  Created by Ilya on 04/06/16.
//  Copyright © 2016 Cengine. All rights reserved.
//

#ifndef BaseImporter_hpp
#define BaseImporter_hpp

#include "ResourceManager.hpp"

template <typename T>
class BaseImporter {
    typedef const std::string const_str;
    
private:
    ResourceManager _resourceManager;
    
    virtual const T& import(const_str& path) = 0;
    
protected:
    template <typename... Args>
    T& addResource(const_str& path, Args&&... args) {
        return _resourceManager.addResource<T>(path, std::forward<Args>(args)...);
    }
    
public:
    virtual ~BaseImporter() {}
    
    const T& getResource(const_str& path) const {
        return static_cast<const T&>(_resourceManager.getResource(path));
    }
    
    void freeResource(const_str& path) { _resourceManager.freeResource(path); }
    
    void freeAll() { _resourceManager.freeAll(); }
};

#endif /* BaseImporter_hpp */
//
//  DefaultMaterial.hpp
//  Flexo
//
//  Created by Ilya on 30/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef DefaultMaterial_hpp
#define DefaultMaterial_hpp

#include "BaseMaterial.hpp"

class DefaultMaterial : public BaseMaterial {
    typedef const std::string const_str;
public:
    DefaultMaterial(const Component::params&, const BaseMaterial::params&);
    
    void activate() const;
};

#endif /* DefaultMaterial_hpp */
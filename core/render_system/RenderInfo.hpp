//
//  RenderInfo.hpp
//  Flexo
//
//  Created by Ilya on 15/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef RenderInfo_hpp
#define RenderInfo_hpp

#include "fmath/mat4.hpp"

#define renderInfo RenderInfo::instance()

class RenderInfo final {
private:
    RenderInfo() {}
public:
    const fmath::mat4* CENGINE_MAT_M;       // current model matrix
    const fmath::mat4* CENGINE_MAT_V;       // current view matrix
    const fmath::mat4* CENGINE_MAT_P;       // current projection matrix
    const fmath::mat4* CENGINE_MAT_MVP;     // current proj*view*model matrix
    const fmath::mat4* CENGINE_MAT_NORMAL;  // current normal matrix
    
    static RenderInfo& instance();
};

#endif /* RenderInfo_hpp */
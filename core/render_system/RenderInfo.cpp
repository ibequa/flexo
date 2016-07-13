//
//  RenderInfo.cpp
//  Flexo
//
//  Created by Ilya on 11/05/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include "RenderInfo.hpp"

RenderInfo& RenderInfo::instance() {
    static RenderInfo ref;
    return ref;
}
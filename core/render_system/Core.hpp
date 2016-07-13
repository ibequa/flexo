//
//  Core.hpp
//  Flexo
//
//  Created by Ilya on 24/02/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#ifndef Core_hpp
#define Core_hpp

#include <string>

class Core final {
public:
    Core(int w, int h, int targetFPS, bool fullScreenMode, const std::string& title);
    
    void gameloop();
};

#endif /* Core_hpp */
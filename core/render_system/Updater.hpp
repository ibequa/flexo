//
//  Updater.hpp
//  Flexo
//
//  Created by Ilya on 27/03/16.
//  Copyright © 2016 Ilya. All rights reserved.
//

#ifndef Updater_hpp
#define Updater_hpp

#define updater Updater::instance()

class Component;

class Updater final {
private:
    Updater() {}
    
public:
    void update();
    void awake();
    
    static Updater& instance();
    
    void setAwaked(Component* const c, bool flag);
    bool isAwaked(Component* const c) const;
};

#endif /* Updater_hpp */
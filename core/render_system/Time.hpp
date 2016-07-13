//
//  Time.hpp
//  Flexo
//
//  Created by Ilya on 10/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef Time_hpp
#define Time_hpp

class Time final {
    friend class Core;
private:
    static int _deltaTime;
    
public:
    /** \brief Returns the time in milliseconds it took to complete the last frame
     */
    static int getDeltaTime();
    
    /** \brief Returns frames per second based on current deltaTime
     */
    static int getCurrentFPS();
};


#endif /* Time_hpp */
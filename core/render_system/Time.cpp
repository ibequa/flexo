//
//  Time.cpp
//  Flexo
//
//  Created by Ilya on 13/04/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#include "Time.hpp"

int Time::_deltaTime = 0;

int Time::getCurrentFPS() { return 1000 / Time::_deltaTime; }

int Time::getDeltaTime() { return _deltaTime; }
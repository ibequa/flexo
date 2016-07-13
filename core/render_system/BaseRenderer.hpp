//
//  BaseRenderer.hpp
//  Flexo
//
//  Created by Ilya on 14/05/16.
//  Copyright © 2016 Flexo. All rights reserved.
//

#ifndef BaseRenderer_hpp
#define BaseRenderer_hpp

#include <map>
#include <vector>
#include "Component.hpp"

class BaseRenderer : public Component {
    typedef std::map<int, std::vector<BaseRenderer*>> int_vec_bsrend_ptr;
    
private:
    int _drawPriority;
    static int_vec_bsrend_ptr _bsRendsPrioritized;
    
protected:
    BaseRenderer(const Component::params&, int drawPriority);
    
    virtual ~BaseRenderer();
    
public:
    static const int_vec_bsrend_ptr& getBaseRenderers();
    
    inline int getDrawPriority() const { return _drawPriority; }
    void setDrawPriority(int value);
    
    virtual void draw() const {}
    virtual void preDrawAll() const {}
    virtual void preSwapBuffers() const {}
};

#endif /* BaseRenderer_hpp */
//
//  DDSTexture.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/10/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef DDSTexture_hpp
#define DDSTexture_hpp

#include <stdio.h>
#include "Texture.hpp"

class DDSTexture: public Texture {
private:
    int format;
    int mipMapCount;
public:
    DDSTexture(int width, int height, int format, int mipMapCount, unsigned char * data);
    virtual void bind();
protected:
    
};

#endif /* DDSTexture_hpp */

//
//  BMPTexture.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/10/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef BMPTexture_hpp
#define BMPTexture_hpp

#include <stdio.h>
#include "Texture.hpp"

class BMPTexture : public Texture {
private:
public:
    BMPTexture(int width, int height, unsigned char * data);
    virtual void bind(int txEnum, int txIdx);
protected:
};

#endif /* BMPTexture_hpp */

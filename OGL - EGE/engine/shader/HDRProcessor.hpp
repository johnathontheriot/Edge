//
//  HDRProcessor.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/28/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef HDRProcessor_hpp
#define HDRProcessor_hpp

#include <stdio.h>
#include "PostProcessor.hpp"

class HighResProcessor: public PostProcessor {
public:
    HighResProcessor(ShaderProgram * shader, Dimensions * d) : PostProcessor(shader, d) {
        this->frame->bind();
        this->addBuffer<HDRTextureBuffer>("texBuffer", new HDRTextureBuffer( d->width, d->height));
        this->addBuffer<DepthBuffer>("depthBuffer", new DepthBuffer(d->width, d->height));
        this->draw();
        this->frame->unbind();
    }
};
#endif /* HDRProcessor_hpp */

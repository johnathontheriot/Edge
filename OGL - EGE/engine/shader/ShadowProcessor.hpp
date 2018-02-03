//
//  ShadowProcessor.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 2/2/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef ShadowProcessor_hpp
#define ShadowProcessor_hpp

#include <stdio.h>
#include "PostProcessor.hpp"

class ShadowProcessor: public PostProcessor {
public:
    ShadowProcessor(ShaderProgram * shader, Dimensions * d) : PostProcessor(shader, d) {
        this->frame->bind();
        this->addBuffer<DepthTextureBuffer>("depthBuffer", new DepthTextureBuffer(d->width, d->height));
        this->draw();
        this->frame->unbind();
    }
};

#endif /* ShadowProcessor_hpp */

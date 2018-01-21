//
//  RenderTextureProcessor.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/18/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef RenderTextureProcessor_hpp
#define RenderTextureProcessor_hpp

#include <stdio.h>
#include "PostProcessor.hpp"
#include "ShaderProgram.hpp"
#include "StorageBuffer.hpp"
#include "System.hpp"

class RenderTextureProcessor: public PostProcessor {
public:
    RenderTextureProcessor(ShaderProgram * shader, Dimensions * d) : PostProcessor(shader, d) {
        this->frame->bind();
        this->addBuffer<TextureBuffer>("texBuffer", new TextureBuffer(d->width, d->height));
        this->addBuffer<DepthBuffer>("depthBuffer", new DepthBuffer(d->width, d->height));
        this->draw();
        this->frame->unbind();
    }
};

#endif /* RenderTextureProcessor_hpp */

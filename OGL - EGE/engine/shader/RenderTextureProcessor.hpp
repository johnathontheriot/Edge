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

class RenderTextureProcessor: public PostProcessor {
public:
    RenderTextureProcessor(ShaderProgram * shader) : PostProcessor(shader) {
        this->frame->bind();
        this->addBuffer<TextureBuffer>("texBuffer", new TextureBuffer(512, 512));
        this->addBuffer<DepthBuffer>("depthBuffer", new DepthBuffer(512, 512));
        this->draw();
        this->frame->unbind();
    }
};

#endif /* RenderTextureProcessor_hpp */

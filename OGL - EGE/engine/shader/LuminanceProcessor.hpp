//
//  LuminanceProcessor.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/28/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef LuminanceProcessor_hpp
#define LuminanceProcessor_hpp

#include <stdio.h>
#include "PostProcessor.hpp"

class LuminanceProcessor: public PostProcessor {
    std::unordered_map<std::string, IGLObject*> * objects;
public:
    LuminanceProcessor(ShaderProgram * shader, Dimensions * d) : PostProcessor(shader, d) {
        this->viewPort->width = this->viewPort->width / 4.0f;
        this->viewPort->height = this->viewPort->height / 4.0f;
        this->objects = new std::unordered_map<std::string, IGLObject*>();
        this->objects->insert({"plane", new GLObject(RectangularPlane::getInstance())});
        this->frame->bind();
        this->addBuffer<LowResTextureBuffer>("texBuffer", new LowResTextureBuffer( d->width / 4.0f,  d->height / 4.0f));
        this->draw();
        this->frame->unbind();
    }
    
    std::unordered_map<std::string, StorageBuffer*> * render(Scene * scene, Dimensions * viewPort, std::unordered_map<std::string, IGLObject*> * objects) {
        return  PostProcessor::render(scene, viewPort, this->objects);
    }
};

#endif /* LuminanceProcessor_hpp */

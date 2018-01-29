//
//  GaussianProcessor.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/28/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef GaussianProcessor_hpp
#define GaussianProcessor_hpp

#include <stdio.h>
#include "PostProcessor.hpp"

class GaussianProcessor: public PostProcessor {
    std::unordered_map<std::string, IGLObject*> * objects;
public:
    GaussianProcessor(ShaderProgram * shader, Dimensions * d) : PostProcessor(shader, d) {
        this->objects = new std::unordered_map<std::string, IGLObject*>();
        this->objects->insert({"plane", new GLObject(RectangularPlane::getInstance())});
        this->frame->bind();
        this->addBuffer<HDRTextureBuffer>("texBuffer", new HDRTextureBuffer( d->width,  d->height));
        this->draw();
        this->frame->unbind();
    }
    
    std::unordered_map<std::string, StorageBuffer*> * render(Scene * scene, Dimensions * viewPort, std::unordered_map<std::string, IGLObject*> * objects) {
        return  PostProcessor::render(scene, viewPort, this->objects);
    }
};

#endif /* GaussianProcessor_hpp */

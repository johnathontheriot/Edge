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
    
    std::unordered_map<std::string, StorageBuffer*> * render(Scene * scene, Dimensions * viewPort, std::unordered_map<std::string, IGLObject*> * objects) {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(2.0f, 4.0f);
        std::unordered_map<std::string, StorageBuffer*> * returnObjects = PostProcessor::render(scene, viewPort, objects);
        glDisable(GL_POLYGON_OFFSET_FILL);
        return returnObjects;
    }
};

#endif /* ShadowProcessor_hpp */

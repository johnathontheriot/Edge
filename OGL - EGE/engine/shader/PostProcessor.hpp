//
//  PostProcessor.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/18/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef PostProcessor_hpp
#define PostProcessor_hpp

#include <stdio.h>
#include "StorageBuffer.hpp"
#include "FrameBuffer.hpp"
#include <unordered_map>
#include "Dimensions.hpp"
#include "GLObject.hpp"

class Scene;
class ShaderProgram;

class PostProcessor {
private:
public:

    GLenum colorAttachment = GL_COLOR_ATTACHMENT0;
    ShaderProgram * shader;
    std::unordered_map<std::string, StorageBuffer*> * buffers;
    FrameBuffer * frame;
    PostProcessor(ShaderProgram * shader) {
        this->frame = new FrameBuffer();
        this->buffers = new std::unordered_map<std::string, StorageBuffer*>();
        this->shader = shader;
    }
    
    template <class BufferType>
    void addBuffer(std::string name, StorageBuffer * buffer) {
        this->buffers->insert({name, buffer});

    }
    
    std::unordered_map<std::string, StorageBuffer*> * render(Scene * scene, Dimensions * viewPort, std::unordered_map<std::string, IGLObject*> * objects) {
        this->frame->bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, 512, 512);
        for (std::unordered_map<std::string, IGLObject*>::const_iterator it = objects->begin(); it != objects->end(); ++it) {
            it->second->render(scene, this->shader);
        }
        this->frame->unbind();
        glViewport(0, 0, viewPort->width * 2 , viewPort->height * 2);
        return this->buffers;
    }
    
    void draw() {
        std::vector<GLenum> * vec = new std::vector<GLenum>();
        for (std::unordered_map<std::string, StorageBuffer*>::const_iterator it = this->buffers->begin(); it != this->buffers->end(); it++) {
            if (it->second->buffer != GL_DEPTH_ATTACHMENT) {
                vec->push_back(it->second->buffer);
            }
        }
        glDrawBuffers(vec->size(), &(*vec)[0]);
    }
    
protected:
};

#endif /* PostProcessor_hpp */

//
//  StorageBuffer.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/18/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef StorageBuffer_hpp
#define StorageBuffer_hpp

#include <stdio.h>
#include "Texture.hpp"
#include "TextureManager.hpp"


class StorageBuffer: public Texture {
public:
    GLenum buffer;
    StorageBuffer(int width, int height): Texture(width, height, NULL) {
    }
    virtual void bindToFrame(GLenum attachment) = 0;
};

class TextureBuffer : public StorageBuffer {
public:
    TextureBuffer(int width, int height): StorageBuffer(width, height) {
        this->texEnum = TextureManager::textureEnum++;
        this->texIndex = TextureManager::textureNumber++;
        glGenTextures(1, &this->id);
        glBindTexture(GL_TEXTURE_2D, this->id);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, this->width, this->height);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    
    void bindToFrame(GLenum attachment) {
        this->buffer = attachment;
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, this->id, 0);
    }
};

class DepthBuffer : public StorageBuffer {
public:
    DepthBuffer(int width, int height): StorageBuffer(width, height) {
        glGenRenderbuffers(1, &this->id);
        glBindRenderbuffer(GL_RENDERBUFFER, this->id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, this->width, this->height);
    }
    
    void bindToFrame(GLenum attachment) {
        this->buffer = attachment;
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, this->id);
    }
    
};

#endif /* StorageBuffer_hpp */

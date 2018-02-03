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
    
    virtual void bindToFrame(GLenum attachment) {
        this->buffer = attachment;
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, this->id, 0);
    }
};

class DepthBuffer : public StorageBuffer {
public:
    DepthBuffer(int width, int height): StorageBuffer(width, height) {
        glGenRenderbuffers(1, &this->id);
        glBindRenderbuffer(GL_RENDERBUFFER, this->id);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, this->width, this->height);
    }
    
    void bindToFrame(GLenum attachment) {
        this->buffer = attachment;
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, this->id);
    }
};

class DepthTextureBuffer : public StorageBuffer {
public:
    DepthTextureBuffer(int width, int height): StorageBuffer(width, height) {
        this->texEnum = TextureManager::textureEnum++;
        this->texIndex = TextureManager::textureNumber++;
        //GLfloat border[] = {1, 0, 0, 0};
        glGenTextures(1, &this->id);
        glBindTexture(GL_TEXTURE_2D, this->id);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, this->width, this->height);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
    }
    
    virtual void bindToFrame(GLenum attachment) {
        this->buffer = attachment;
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, this->id, 0);
    }
};

class HDRTextureBuffer : public StorageBuffer {
public:
    HDRTextureBuffer(int width, int height): StorageBuffer(width, height) {
        this->texEnum = TextureManager::textureEnum++;
        this->texIndex = TextureManager::textureNumber++;
        glGenTextures(1, &this->id);
        glBindTexture(GL_TEXTURE_2D, this->id);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, this->width, this->height);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    
    void bindToFrame(GLenum attachment) {
        this->buffer = attachment;
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, this->id, 0);
    }
};

class LowResTextureBuffer : public StorageBuffer {
public:
    LowResTextureBuffer(int width, int height): StorageBuffer(width, height) {
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

#endif /* StorageBuffer_hpp */

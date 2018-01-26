//
//  FrameBuffer.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/17/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef FrameBuffer_hpp
#define FrameBuffer_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class FrameBuffer {
private:
public:
    GLuint id;
    FrameBuffer() {
        glGenFramebuffers(1, &this->id);
    }
    void bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, this->id);
    }
    void unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};

#endif /* FrameBuffer_hpp */

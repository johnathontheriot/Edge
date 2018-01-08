//
//  Geometry.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.hpp"
#include <glm/mat4x4.hpp>

class Geometry {
private:
    friend class GLObject;
public:
    Geometry();
    Geometry(GLfloat *, int, GLfloat *);
protected:
    GLfloat * vertexBuffer;
    GLfloat * uvBuffer;
    int vertexBufferSize;
    GLenum drawType;
    GLuint VAOid;
    GLuint VBOid;
    GLuint UVOid;
    void createVAO(GLuint &);
    void createBuffer(GLuint &);
    void bindVAO(GLuint &);
    template <class BufferType> void bindBuffer(GLuint & bufferID, BufferType * data, int size) {
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(BufferType) * size, data, GL_STATIC_DRAW);
    }
};

#endif

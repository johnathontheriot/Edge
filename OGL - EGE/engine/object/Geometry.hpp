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
    Geometry(GLfloat *, int);
protected:
    GLfloat * vertexBuffer;
    int vertexBufferSize;
    GLenum drawType;
    GLuint VAOid;
    GLuint VBOid;
    void createVAO(GLuint &);
    void createBuffer(GLuint &);
    void bindVAO(GLuint &);
    void bindVertices(GLuint &);
};

#endif

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
#include "BufferObject.hpp"
#include <unordered_map>

class Geometry {
private:
    friend class GLObject;
public:
    void updateUVs(GLfloat * uvs, int size);
    void updateVertices(GLfloat * uvs, int size);
    Geometry();
    Geometry(GLfloat *, int, GLfloat *);
protected:
    std::unordered_map<std::string, BufferObject*> * buffers;
    GLenum drawType;
    GLuint VAOid;
    void createVAO(GLuint &);
    void bindVAO(GLuint &);
    void bindBuffers();
    int bufferListSize = 0;
    int getVertexBufferSize(std::string key);
};

#endif

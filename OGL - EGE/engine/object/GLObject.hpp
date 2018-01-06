//
//  GLObject.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef GLObject_hpp
#define GLObject_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../shader/ShaderProgram.hpp"

class GLObject {
private:
    GLuint VAOid;
    GLuint VBOid;
    GLfloat * vertexBuffer;
    int vertexBufferSize;
    ShaderProgram * shader;
    void createVAO(GLuint &);
    void createBuffer(GLuint &);
    void bindVAO(GLuint &);
    void bindVertices(GLuint &);
    
public:
    GLObject(GLfloat *, int);
    void render(GLenum = GL_TRIANGLES);
    void setProgram(ShaderProgram *);
};

#endif /* GLObject_hpp */

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
#include <glm/mat4x4.hpp>
#include "Scene.hpp"

class ShaderProgram;
class Scene;

class GLObject {
private:
    GLuint VAOid;
    GLuint VBOid;
    glm::mat4x4 modelMatrix;
    glm::mat4x4 localScale;
    glm::mat4x4 localTranslation;
    glm::mat4x4 localRotation;
    glm::mat4x4 globalScale;
    glm::mat4x4 globalTranslation;
    glm::mat4x4 globalRotation;
    GLfloat * vertexBuffer;
    int vertexBufferSize;
    void createVAO(GLuint &);
    void createBuffer(GLuint &);
    void bindVAO(GLuint &);
    void bindVertices(GLuint &);
    
public:
    ShaderProgram * shader;
    glm::mat4x4 getModelMatrix();
    glm::mat4x4 getLocalModelMatrix();
    glm::mat4x4 getGlobalModelMatrix();
    void translateLocal(GLfloat x, GLfloat y, GLfloat z);
    void scaleLocal(GLfloat x, GLfloat y, GLfloat z);
    void rotateLocal(GLfloat x, GLfloat y, GLfloat z);
    void translateGlobal(GLfloat x, GLfloat y, GLfloat z);
    void scaleGlobal(GLfloat x, GLfloat y, GLfloat z);
    void rotateGlobal(GLfloat x, GLfloat y, GLfloat z);
    GLObject(GLfloat *, int);
    void render(Scene*, GLenum = GL_TRIANGLES);
    void setProgram(ShaderProgram *);
};

#endif /* GLObject_hpp */

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
#include "ShaderProgram.hpp"
#include <glm/mat4x4.hpp>
#include "Scene.hpp"
#include "../physics/Script.hpp"

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
    void tick();
    std::unordered_map<std::string, Script<GLObject>*> * scripts;
    template <class ScriptType> void attachScript(std::string name) {
        ScriptType * script = new ScriptType();
        this->scripts->insert({name, script});
    }
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

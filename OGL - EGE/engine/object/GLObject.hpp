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
#include "../physics/Script.hpp"
#include "Geometry.hpp"
#include "Texture.hpp"
#include <vector>

class ShaderProgram;
class Scene;
class Geometry;

class IGLObject: public IShaderVariable, public IScriptable {
public:
    virtual void render(Scene * scene, ShaderProgram* program = NULL) {
        
    }
};

class GLObject: public IGLObject  {
private:
    glm::mat4x4 modelMatrix;
    glm::mat4x4 localScale;
    glm::mat4x4 localTranslation;
    glm::mat4x4 localRotation;
    glm::mat4x4 globalScale;
    glm::mat4x4 globalTranslation;
    glm::mat4x4 globalRotation;
    int dimension = 3;
public:
    void (*toShaderVariable)(std::string, ShaderProgram*) = NULL;
    ShaderProgram * shader;
    std::vector<Texture*> * textures;
    template <class ScriptType>
    void attachScript(std::string name) {
        IScriptable::attachScript<ScriptType, GLObject>(name);
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
    GLObject(Geometry * mesh);
    GLObject();
    virtual void render(Scene*, ShaderProgram* program = NULL);
    void setProgram(ShaderProgram *);
    Geometry * geometry;
    virtual void bind(std::string name, ShaderProgram * shader) {
        if (this->toShaderVariable) {
            this->toShaderVariable(name, shader);
        }
    }
protected:
    

};

#endif /* GLObject_hpp */

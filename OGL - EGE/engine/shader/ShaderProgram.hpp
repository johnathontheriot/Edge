//
//  ShaderProgram.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include "GLSLShader.hpp"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

class GLObject;
class Scene;
class ShaderProgram;

class IShaderVariable {
private:
    friend class ShaderProgram;
protected:
    virtual void bind(std::string varName, ShaderProgram * shader) = 0;
    
    template<class VariableType>
    void bind(std::string varName, ShaderProgram * shader) {
        VariableType * c = ((VariableType*)this);
        c->bind(varName, shader);
    }
};

class ShaderProgram {
private:
    GLSLShader * vertexShader;
    GLSLShader * fragmentShader;
    GLSLShader * geometryShader;
public:
    std::function<void(GLObject*, Scene*)> bindVars = NULL;
    void bindVariable(std::string, glm::mat4x4);
    void bindVariable(std::string, glm::vec4);
    void bindVariable(std::string, glm::vec3);
    void bindVariable(std::string, GLfloat);
    GLuint id;
    void bind(GLObject*, Scene *);
    ShaderProgram(GLSLShader *, GLSLShader *, GLSLShader *);
    ShaderProgram(GLSLShader *, GLSLShader *);
    void bindVariable(std::string name, IShaderVariable * var);
    template<class VariableType, typename std::enable_if<std::is_base_of<IShaderVariable, VariableType>::value>::type* = nullptr>
    void bindVariable(std::string name, IShaderVariable * var) {
        var->bind<VariableType>(name, this);
    }


};

#endif /* ShaderProgram_hpp */

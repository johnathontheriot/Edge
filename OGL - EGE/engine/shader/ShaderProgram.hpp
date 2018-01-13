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
#include "../object/GLObject.hpp"
#include <glm/mat4x4.hpp>
#include "../object/scene/Scene.hpp"
#include "Texture.hpp"

class GLObject;
class Scene;

class ShaderProgram {
private:
    GLSLShader * vertexShader;
    GLSLShader * fragmentShader;
    GLSLShader * geometryShader;
public:
    void (*bindVars)(GLObject*, Scene*) = NULL;
    void bind4fMatrix(std::string, glm::mat4x4);
    void bindTexture(std::string name, Texture * texture);
    void bindCubeMap(std::string name, Texture * texture);

    GLuint id;
    void bind(GLObject*, Scene *);
    ShaderProgram(GLSLShader *, GLSLShader *, GLSLShader *);
    ShaderProgram(GLSLShader *, GLSLShader *);
};

#endif /* ShaderProgram_hpp */

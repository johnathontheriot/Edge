//
//  GLSLShader.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef GLSLShader_hpp
#define GLSLShader_hpp

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLSLShader {
private:
public:    
    GLuint shaderID;
    GLSLShader(GLuint);
};

#endif /* GLSLShader_hpp */

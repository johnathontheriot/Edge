//
//  main.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/5/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine/system/System.hpp"
#include "engine/object/GLObject.hpp"
#include "engine/shader/ShaderManager.hpp"
#include "engine/object/Scene.hpp"



int main(int argc, const char * argv[]) {
    // Hardcoded for now - will be accepted through command line
    System::configPath = "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/taco.config.json";
    
    if (!glfwInit()) {
    
    }
    // can add to config but probably not a great idea - should set this
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // initialize system with single window
    System * system = System::getInstance();
    glfwMakeContextCurrent(system->windows->at("main"));
    glewExperimental = GL_TRUE;
    if (!glewInit()) {
        
    }
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    Scene * scene = new Scene();
    scene->objects->insert({"Triange1", new GLObject(new GLfloat [9] {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    }, 9)});
    ShaderProgram * shader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/solid.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/solid.fragment.glsl");
    scene->objects->at("Triange1")->setProgram(shader);
    // can set bindVars event on shader here to change active camera, bind new vars, etc.
    while(!system->shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene->render();
        glfwSwapBuffers(system->windows->at("main"));
        glfwPollEvents();
    }
}







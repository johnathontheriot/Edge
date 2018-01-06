//
//  main.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/5/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "System.hpp"


void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    
}


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
    while(!system->shouldClose()) {
        /*
         This wont exist - will replace with
         a call to scene render. Haven't decided by which means yet.
         Will probably allow user to bind scenes to a window, then will bind
         each window, calling render on each of their bound scenes. 
         
         Just starting with default main window for now.
        */
        render();
        glfwSwapBuffers(system->windows->at("main"));
        glfwPollEvents();
    }
}







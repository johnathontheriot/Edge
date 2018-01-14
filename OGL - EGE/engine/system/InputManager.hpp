//
//  InputManager.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/8/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef InputManager_hpp
#define InputManager_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "System.hpp"
#include <glm/vec2.hpp>
#include <unordered_map>

class InputManager {
private:
    InputManager();
public:
    std::unordered_map<std::string, char> * pressed;
    bool keyDown(std::string key);
    std::unordered_map<std::string, std::function<void(double, double)>> * scrollCallbacks;
    glm::dvec2 * lastPolledMousePosition;
    static InputManager * Instance;
    static InputManager * getInstance();
    bool isKeyPressed(std::string key);
    bool isMouseDown(std::string button);
    void mouseDelta(GLfloat & deltaX, GLfloat & deltaY);
    void mousePosition(double & deltaX, double & deltaY);
    void addScrollEvent(std::string, std::function<void(double, double)>);
    void removeScrollEvent(std::string);
};

#endif /* InputManager_hpp */

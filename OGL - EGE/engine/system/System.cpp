//
//  System.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/5/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../vendor/json.hpp"
#include "System.hpp"
#include "WindowConfig.hpp"
#include "../object/scene/Scene.hpp"
#include "../object/scene/SceneManager.hpp"

using json = nlohmann::json;

System * System::Instance;
std::string System::configPath;

System::System() {
    if (!glfwInit()) {
        
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::string fileData = System::readFile(System::configPath);
    json systemConfig = json::parse(fileData);
    this->primaryMonitor = glfwGetPrimaryMonitor();
    this->monitors = glfwGetMonitors(&this->monitorCount);
    this->windows = new std::unordered_map<std::string, GLFWwindow*>();
    this->addWindow(new WindowConfig(systemConfig));
    glfwMakeContextCurrent(this->windows->at("main"));
    this->activeWindow = this->windows->at("main");
    glewExperimental = GL_TRUE;
    if (!glewInit()) {
        
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
}

std::string System::readFile(std::string path) {
    std::ifstream fileStream(path);
    fileStream.seekg(0, std::ios::end);
    size_t size = fileStream.tellg();
    std::string buffer(size, ' ');
    fileStream.seekg(0);
    fileStream.read(&buffer[0], size);
    return buffer;
}

System * System::getInstance() {
    if (!System::Instance) {
        System::Instance = new System();
    }
    return System::Instance;
}

/*
    Will get more complicated later
 */
bool System::shouldClose() {
    return this->monitorCount == 0;
}

void System::start() {
    while(!this->shouldClose()) {
        for (std::unordered_map<std::string, Scene*>::const_iterator it = SceneManager::getInstance()->scenes->begin(); it != SceneManager::getInstance()->scenes->end(); ++it) {
            
            it->second->render();
        }
        for( std::unordered_map<std::string, GLFWwindow*>::const_iterator it = this->windows->begin(); it != this->windows->end(); ++it ) {
            glfwSwapBuffers(it->second);
        }
        for (std::unordered_map<std::string, Scene*>::const_iterator it = SceneManager::getInstance()->scenes->begin(); it != SceneManager::getInstance()->scenes->end(); ++it) {
            it->second->tick();
        }

        glfwPollEvents();
    }
}

GLFWwindow * System::getActiveWindow() {
    return this->activeWindow;
}

void System::setActiveWindow(std::string name) {
    this->activeWindow = this->windows->at(name);
}

void System::setActiveWindow(GLFWwindow * window) {
    this->activeWindow = window;
}


GLFWwindow * System::addWindow(WindowConfig * config) {
    GLFWwindow * window = glfwCreateWindow(config->width, config->height, config->title.c_str(), config->fullScreen ? this->primaryMonitor : NULL, NULL);
    this->windows->insert({config->name, window});
    return window;
}

Dimensions System::getWindowDimenions(std::string name) {
    int width;
    int height;
    glfwGetWindowSize(this->windows->at(name), &width, &height);
    return Dimensions(width, height);
}

Dimensions System::getWindowDimenions(GLFWwindow * window) {
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    return Dimensions(width, height);
}


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


using json = nlohmann::json;

System * System::Instance;
std::string System::configPath;

System::System() {
    std::string fileData = System::readFile(System::configPath);
    json systemConfig = json::parse(fileData);
    this->primaryMonitor = glfwGetPrimaryMonitor();
    this->monitors = glfwGetMonitors(&this->monitorCount);
    this->windows = new std::unordered_map<std::string, GLFWwindow*>();
    this->addWindow(new WindowConfig(systemConfig));
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

bool System::shouldClose() {
    return this->monitorCount == 0;
}

    
GLFWwindow * System::addWindow(WindowConfig * config) {
    GLFWwindow * window = glfwCreateWindow(config->width, config->height, config->title.c_str(), config->fullScreen ? this->primaryMonitor : NULL, NULL);
    this->windows->insert({config->name, window});
    return window;
}

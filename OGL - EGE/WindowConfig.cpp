//
//  WindowConfig.cpp
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
#include "json.hpp"
#include "WindowConfig.hpp"

using json = nlohmann::json;


WindowConfig::WindowConfig(json config) {
    this->width = config["width"];
    this->height = config["height"];
    this->title = config["title"];
    this->name = config["name"];
}

//
//  System.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/5/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef System_hpp
#define System_hpp

#include <unordered_map>
#include "WindowConfig.hpp"
#include "../../vendor/json.hpp"
#include "../object/scene/Scene.hpp"

using json = nlohmann::json;

struct Dimensions{
    float width;
    float height;
    Dimensions(int width, int height) {
        this->width = 1.0 * width;
        this->height = 1.0 * height;
    }
};

class System {
private:
    int monitorCount = 0;
    GLFWmonitor * primaryMonitor;
    GLFWmonitor ** monitors;
    System();
public:
    static System * Instance;
    static std::string readFile(std::string path);
    static std::string configPath;
    static System * getInstance();
    bool shouldClose();
    GLFWwindow * addWindow(WindowConfig * config);
    std::unordered_map<std::string, GLFWwindow*> * windows;
    Dimensions getWindowDimenions(std::string name);
    Dimensions getWindowDimenions(GLFWwindow * window);
    void start();

};
#endif /* System_hpp */

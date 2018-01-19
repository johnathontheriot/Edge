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
#include "Dimensions.hpp"

using json = nlohmann::json;

class System {
private:
    int monitorCount = 0;
    GLFWmonitor * primaryMonitor;
    GLFWmonitor ** monitors;
    GLFWwindow * activeWindow;
    System();
public:
    static System * Instance;
    static std::string readFile(std::string path);
    static std::string configPath;
    static System * getInstance();
    bool shouldClose();
    GLFWwindow * addWindow(WindowConfig * config);
    GLFWwindow * getActiveWindow();
    void setActiveWindow(std::string name);
    void setActiveWindow(GLFWwindow * window);
    std::unordered_map<std::string, GLFWwindow*> * windows;
    Dimensions getWindowDimenions(std::string name);
    Dimensions getWindowDimenions(GLFWwindow * window);
    void start();

};
#endif /* System_hpp */

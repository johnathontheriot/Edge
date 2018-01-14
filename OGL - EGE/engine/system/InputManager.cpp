//
//  InputManager.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/8/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "InputManager.hpp"

InputManager * InputManager::Instance;


InputManager * InputManager::getInstance() {
    if (!InputManager::Instance) {
        InputManager::Instance = new InputManager();
    }
    return InputManager::Instance;
}

void scrollWheelCallback(GLFWwindow* window, double xoffset, double yoffset) {
    InputManager * manager = InputManager::getInstance();
    for (std::unordered_map<std::string, std::function<void(double, double)>>::const_iterator it = manager->scrollCallbacks->begin(); it != manager->scrollCallbacks->end(); ++it) {
        it->second(xoffset, yoffset);
    }

}


void mouseClickCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        glm::dvec2 * pos = new glm::dvec2(0.0, 0.0);
        glfwGetCursorPos(System::getInstance()->getActiveWindow(), &(pos->x), &(pos->y));
        InputManager::getInstance()->lastPolledMousePosition = pos;
    }
}


InputManager::InputManager() {
    this->pressed = new std::unordered_map<std::string, char>();
    glfwSetMouseButtonCallback(System::getInstance()->getActiveWindow(), mouseClickCallback);
    glfwSetScrollCallback(System::getInstance()->getActiveWindow(), scrollWheelCallback);
    this->scrollCallbacks = new std::unordered_map<std::string, std::function<void(double, double)>>;
}

bool InputManager::keyDown(std::string key) {
    if (!this->pressed->count(key) && this->isKeyPressed(key)) {
        this->pressed->insert({key, NULL});
        return true;
    }
    else if (this->pressed->count(key) && !this->isKeyPressed(key)) {
        this->pressed->erase(key);
    }
    return false;
}


bool InputManager::isKeyPressed(std::string key) {
    GLFWwindow * window = System::getInstance()->getActiveWindow();
    if (key.length() == 1) {
        return glfwGetKey(window, toupper(key[0])) == GLFW_PRESS;
    } else {
        if (key == "space") {
            return glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
        }
        else if (key == "comma") {
            return glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS;
        }
        else if (key == "period") {
            return glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS;
        }
    }
    return false;
}

bool InputManager::isMouseDown(std::string button) {
    if (button == "left") {
        return glfwGetMouseButton(System::getInstance()->getActiveWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    }
    else if (button == "right") {
        return glfwGetMouseButton(System::getInstance()->getActiveWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    }
    return false;
}

void InputManager::addScrollEvent(std::string key, std::function<void(double, double)> callback) {
    this->scrollCallbacks->insert({key, callback});
}

void InputManager::removeScrollEvent(std::string key) {
    this->scrollCallbacks->erase(key);
}

void InputManager::mouseDelta(GLfloat & deltaX, GLfloat & deltaY) {
    glm::dvec2 * pos = new glm::dvec2(0.0, 0.0);
    glfwGetCursorPos(System::getInstance()->getActiveWindow(), &(pos->x), &(pos->y));
    if (!this->lastPolledMousePosition) {
        deltaX = 0.0;
        deltaY = 0.0;
    }
    else {
        deltaX = pos->x - this->lastPolledMousePosition->x;
        deltaY = pos->y - this->lastPolledMousePosition->y;
    }
    this->lastPolledMousePosition = pos;
}


void InputManager::mousePosition(double & deltaX, double & deltaY) {
    glfwGetCursorPos(System::getInstance()->getActiveWindow(), &deltaX, &deltaY);
    
}

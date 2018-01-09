////
////  BasicMovement.cpp
////  OGL - EGE
////
////  Created by Johnathon Theriot on 1/8/18.
////  Copyright © 2018 Johnathon Theriot. All rights reserved.
////
//
//#include "BasicMovement.hpp"
//#include "System.hpp"
//
//static bool down = false;
//static double xLoc = 0;
//static double yLoc = 0;
//
//void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
//    SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->zoom(yoffset * .06);
//}
//
//static void moveCallback(GLFWwindow* window, double xpos, double ypos) {
//    if (down) {
//        double newX = xpos;
//        double newY = ypos;
//        double o1 = xLoc;
//        double o2 = yLoc;
//        if (newX != xLoc || newY != yLoc) {
//            SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->moveCamera((newX - xLoc) * (.006f), (newY - yLoc) * (.006f));
//            xLoc = newX;
//            yLoc = newY;
//        }
//    }
//    
//}
//
//void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//    if (key == GLFW_KEY_W) {
//        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->translateGlobal(0, 0, .0001);
//    }
//    if (key == GLFW_KEY_A) {
//        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->translateGlobal(-.0001, 0, 0);
//    }
//    if (key == GLFW_KEY_S) {
//        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->translateGlobal(0, 0, -.0001);
//    }
//    if (key == GLFW_KEY_D) {
//        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->translateGlobal(.0001, 0, 0);
//    }
//    if (key == GLFW_KEY_COMMA) {
//        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->changeFOV(.4);
//    }
//    if (key == GLFW_KEY_PERIOD) {
//        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->changeFOV(-.4);
//    }
//}
//
//void callback(GLFWwindow* window, int button, int action, int mods) {
//    
//    if (button == GLFW_MOUSE_BUTTON_LEFT) {
//        if (action == GLFW_PRESS && !down) {
//            down = true;
//            glfwGetCursorPos(window, &xLoc, &yLoc);
//        }
//        else if (action == GLFW_RELEASE) {
//            down = false;
//        }
//    }
//}
//
//void BasicMovement::tick(Camera * target) {
//    System * system = System::getInstance();
////    glfwSetMouseButtonCallback(system->windows->at("main"), callback);
//    glfwSetCursorPosCallback(system->windows->at("main"), moveCallback);
//    glfwSetScrollCallback(system->windows->at("main"), scrollCallback);
//    glfwSetKeyCallback(system->windows->at("main"), keyCallback);
//}
//

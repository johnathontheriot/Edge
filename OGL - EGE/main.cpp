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
#include "engine/object/scene/Scene.hpp"
#include "engine/object/scene/SceneManager.hpp"
#include "Spin.hpp"
#include "Geometry.hpp"
#include "Cube.hpp"
#include "TextureManager.hpp"

static bool down = false;
static double xLoc = 0;
static double yLoc = 0;

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->zoom(yoffset * .06);
}

static void moveCallback(GLFWwindow* window, double xpos, double ypos) {
    if (down) {
        double newX = xpos;
        double newY = ypos;
        double o1 = xLoc;
        double o2 = yLoc;
        if (newX != xLoc || newY != yLoc) {
            SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->moveCamera((newX - xLoc) * (.006f), (newY - yLoc) * (.006f));
            xLoc = newX;
            yLoc = newY;
        }
    }

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W) {
        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->translateGlobal(0, 0, .0001);
    }
    if (key == GLFW_KEY_A) {
        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->translateGlobal(-.0001, 0, 0);
    }
    if (key == GLFW_KEY_S) {
        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->translateGlobal(0, 0, -.0001);
    }
    if (key == GLFW_KEY_D) {
        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->translateGlobal(.0001, 0, 0);
    }
    if (key == GLFW_KEY_COMMA) {
        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->changeFOV(.4);
    }
    if (key == GLFW_KEY_PERIOD) {
        SceneManager::getInstance()->scenes->at("main")->cameras->at("main")->changeFOV(-.4);
    }
}

void callback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS && !down) {
            down = true;
            glfwGetCursorPos(window, &xLoc, &yLoc);
        }
        else if (action == GLFW_RELEASE) {
            down = false;
        }
    }
}

int main(int argc, const char * argv[]) {
    // Hardcoded for now - will be accepted through command line
    System::configPath = "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/taco.config.json";
    
    System * system = System::getInstance();
    Scene * scene = new Scene(system->windows->at("main"));
    scene->objects->insert({"Triange1", new GLObject(Cube::getInstance())});
    ShaderProgram * shader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/solid.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/solid.fragment.glsl");

    shader->bindVars = [](GLObject* obj, Scene* scene) {
        obj->shader->bind4fMatrix("modelTransform", obj->getModelMatrix());
        // add bind camera function
        obj->shader->bind4fMatrix("viewTransform", scene->cameras->at("main")->getViewMatrix());
        obj->shader->bind4fMatrix("projectionTransform", scene->cameras->at("main")->getProjectionMatrix());
        obj->shader->bindTexture("tex", obj->textures->at(0), GL_TEXTURE0, 0);
    };
    
    scene->objects->at("Triange1")->textures->push_back(TextureManager::getInstance()->loadTexture("pattern", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/color.bmp"));
    scene->objects->at("Triange1")->setProgram(shader);
    scene->objects->at("Triange1")->scaleLocal(.1, .1, .1);
    //scene->objects->at("Triange1")->translateLocal(0, 0, 1);
    scene->objects->at("Triange1")->attachScript<Spin>("spinner");
    SceneManager::getInstance()->scenes->insert({"main", scene});
    glfwSetMouseButtonCallback(system->windows->at("main"), callback);
    glfwSetCursorPosCallback(system->windows->at("main"), moveCallback);
    glfwSetScrollCallback(system->windows->at("main"), scrollCallback);
    glfwSetKeyCallback(system->windows->at("main"), keyCallback);
    system->start();
}




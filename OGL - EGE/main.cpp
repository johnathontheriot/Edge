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

int main(int argc, const char * argv[]) {
    // Hardcoded for now - will be accepted through command line
    System::configPath = "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/taco.config.json";
    
    System * system = System::getInstance();
    
    Scene * scene = new Scene();
    scene->objects->insert({"Triange1", new GLObject(Cube::getInstance())});
    ShaderProgram * shader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/solid.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/solid.fragment.glsl");

    shader->bindVars = [](GLObject* obj, Scene* scene) {
        obj->shader->bind4fMatrix("modelTransform", obj->getModelMatrix());
        obj->shader->bind4fMatrix("viewTransform", scene->cameras->at("main")->viewMatrix);
        obj->shader->bindTexture("tex", obj->textures->at(0), GL_TEXTURE0, 0);
    };
    
    scene->objects->at("Triange1")->textures->push_back(TextureManager::getInstance()->loadTexture("pattern", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/color.bmp"));
    scene->objects->at("Triange1")->setProgram(shader);
    scene->objects->at("Triange1")->scaleLocal(.5, .5, .5);
    scene->objects->at("Triange1")->attachScript<Spin>("spinner");
    SceneManager::getInstance()->scenes->insert({"main", scene});
    system->start();
}

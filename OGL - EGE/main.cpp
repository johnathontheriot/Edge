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
#include "BasicMovement.hpp"
#include "RectangularPlane.hpp"
#include "TextBox.hpp"
#include "BMPTexture.hpp"
#include "DDSTexture.hpp"
#include "SkyBox.hpp"

int main(int argc, const char * argv[]) {
    // Hardcoded for now - will be accepted through command line
    System::configPath = "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/taco.config.json";
    
    System * system = System::getInstance();
    Scene * scene = new Scene(system->getActiveWindow());
    
    ShaderProgram * shader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/solid.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/solid.fragment.glsl");

    shader->bindVars = [](GLObject* obj, Scene* scene) {
        obj->shader->bind4fMatrix("modelTransform", obj->getModelMatrix());
        // add bind camera function
        obj->shader->bind4fMatrix("viewTransform", scene->cameras->at("main")->getViewMatrix());
        obj->shader->bind4fMatrix("projectionTransform", scene->cameras->at("main")->getProjectionMatrix());
        obj->shader->bindTexture("tex", obj->textures->at(0), GL_TEXTURE0, 0);
    };
    
    scene->objects->insert({"title1", new TextBox("This is a cube!")});
    scene->objects->at("title1")->scaleLocal(.1, .1, .1);
    scene->objects->at("title1")->translateGlobal(0, .65f, 0);
    
    scene->objects->insert({"Cube1", new GLObject(Cube::getInstance())});
    scene->objects->at("Cube1")->textures->push_back(TextureManager::getInstance()->loadTexture<BMPTexture>("crate", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/crate.bmp"));
    scene->objects->at("Cube1")->setProgram(shader);
    scene->objects->at("Cube1")->scaleLocal(.5, .5, .5);
    scene->objects->at("Cube1")->translateGlobal(0, 0, -.53f);
    
    scene->objects->insert({"Plane1", new GLObject(RectangularPlane::getInstance())});
    scene->objects->at("Plane1")->textures->push_back(TextureManager::getInstance()->loadTexture<BMPTexture>("ground", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/wood_flooring.bmp"));
    scene->objects->at("Plane1")->setProgram(shader);
    scene->objects->at("Plane1")->scaleLocal(5, 5, 5);
    scene->objects->at("Plane1")->rotateLocal(M_PI / 2, 0, 0);
    scene->objects->at("Plane1")->translateGlobal(0, -.501, -.53f);
    
    scene->cameras->at("main")->translateGlobal(0, 0, -2.1);
    scene->cameras->at("main")->attachScript<BasicMovement>("movement");
    
    scene->objects->insert({"brick", new SkyBox("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/cloud.bmp")});
    
    SceneManager::getInstance()->scenes->insert({"main", scene});
    system->start();
}




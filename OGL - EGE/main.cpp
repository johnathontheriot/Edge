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
#include "Light.hpp"
#include "RenderTextureProcessor.hpp"
#include "ParticleSystem.hpp"
#include "BloomProcessor.hpp"

int main(int argc, const char * argv[]) {
    // Hardcoded for now - will be accepted through command line
    System::configPath = "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/taco.config.json";
    
    System * system = System::getInstance();
    Scene * scene = new Scene(system->getActiveWindow());
    
    BloomProcessor * bloom = new BloomProcessor(new Dimensions(1600, 900));

    ShaderProgram * lightingShader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/phong_lighting.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/phong_lighting.fragment.glsl");
    
    lightingShader->bindVars = [bloom](ShaderProgram * shader, GLObject* obj, Scene* scene) {
        shader->bindVariable("modelTransform", obj->getModelMatrix());
        shader->bindVariable("invTransMV", glm::transpose(glm::inverse(scene->cameras->at("main")->getViewMatrix() * obj->getModelMatrix())));
        shader->bindVariable<Camera>("main", scene->cameras->at("main"));
        shader->bindVariable<Texture>("tex", obj->textures->at(0));
        shader->bindVariable<Light>("light", scene->objects->at("light1"));
        //shader->bindVariable<Texture>("envtex", scene->get<SkyBox>("skyBox")->textures->at(0));
        //shader->bindVariable("cmapTransform", scene->get<SkyBox>("skyBox")->getModelMatrix());
        shader->bindVariable("reflection", 100);
    };

    scene->effectsPipeline->insert(scene->effectsPipeline->begin(), bloom->processors->begin(), bloom->processors->end());
    scene->objects->insert({"title1", new TextBox("This is a cube!", 0x20437CFF)});
    
    scene->get<TextBox>("title1")->scaleLocal(.1, .1, .1);
    scene->get<TextBox>("title1")->translateGlobal(0, .65f, 0);
    
    scene->objects->insert({"Cube1", new GLObject(Cube::getInstance())});
    scene->get<GLObject>("Cube1")->textures->push_back(TextureManager::getInstance()->loadTexture<BMPTexture>("crate", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/crate.bmp"));
    scene->get<GLObject>("Cube1")->setProgram(lightingShader);
    scene->get<GLObject>("Cube1")->scaleLocal(.5, .5, .5);
    
    std::string f = "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/";
    //scene->objects->insert({"skyBox", new SkyBox(f + "s4.bmp", f + "s2.bmp", f + "s1.bmp", f + "s5.bmp", f + "s6.bmp", f + "s3.bmp")});
    //scene->get<SkyBox>("skyBox")->rotateGlobal(M_PI, 0, 0);
    
    scene->objects->insert({"Plane1", new GLObject(RectangularPlane::getInstance())});
    scene->get<GLObject>("Plane1")->textures->push_back(TextureManager::getInstance()->loadTexture<BMPTexture>("ground", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/wood_flooring.bmp"));
    scene->get<GLObject>("Plane1")->setProgram(lightingShader);
    scene->get<GLObject>("Plane1")->scaleLocal(5, 5, 5);
    scene->get<GLObject>("Plane1")->rotateLocal(M_PI / 2, 0, 0);
    scene->get<GLObject>("Plane1")->translateGlobal(0, -.501, -.53f);
    
    scene->objects->insert({"light1", new Light()});
    scene->get<Light>("light1")->translateGlobal(0, 0, 2.1);
    scene->get<Light>("light1")->attachScript<Spin>("lightMvmnt");
    
    
    scene->cameras->at("main")->translateGlobal(0, 0, -2.1);
    scene->cameras->at("main")->attachScript<BasicMovement>("movement");
    

    
    SceneManager::getInstance()->scenes->insert({"main", scene});
    system->start();
}




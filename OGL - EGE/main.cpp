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
#include <glm/gtc/matrix_transform.hpp>
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
#include "BloomScript.hpp"
#include "ShadowProcessor.hpp"

int main(int argc, const char * argv[]) {
    // Hardcoded for now - will be accepted through command line
    System::configPath = "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/taco.config.json";
    
    System * system = System::getInstance();
    Scene * scene = new Scene(system->getActiveWindow());
    
    std::string f = "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/";
    scene->objects->insert({"skyBox", new SkyBox(f + "s4.bmp", f + "s2.bmp", f + "s1.bmp", f + "s5.bmp", f + "s6.bmp", f + "s3.bmp")});
    scene->get<SkyBox>("skyBox")->rotateGlobal(M_PI, 0, 0);

    ShaderProgram * lightingShader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/phong_lighting.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/phong_lighting.fragment.glsl");
    
    ShaderProgram * depthShader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/depth.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/depth.fragment.glsl");
    depthShader->bindVars = [](ShaderProgram * shader, GLObject* obj, Scene* scene) {
        shader->bindVariable("modelTransform", obj->getModelMatrix());
        shader->bindVariable("main_projectionTransform", scene->cameras->at("main")->getProjectionMatrix(ProjectionType::ORTHOGRAPHIC, -10.0f, 10.0f, 10.0f, -10.0f, -10.0f, 20.0f));
        shader->bindVariable("main_viewTransform", glm::lookAt(scene->get<Light>("light1")->getPosition(), glm::vec3(0,0,0), glm::vec3(0,1,0)));
    };
    
    ShadowProcessor * shadows = new ShadowProcessor(depthShader, new Dimensions(1600, 900));
    scene->effectsPipeline->push_back(shadows);
    
    
    lightingShader->bindVars = [shadows](ShaderProgram * shader, GLObject* obj, Scene* scene) {
        shader->bindVariable("modelTransform", obj->getModelMatrix());
        shader->bindVariable("invTransMV", glm::transpose(glm::inverse(scene->cameras->at("main")->getViewMatrix() * obj->getModelMatrix())));
        shader->bindVariable<Camera>("main", scene->cameras->at("main"));
        shader->bindVariable<Texture>("tex", shadows->buffers->at("depthBuffer"));
        shader->bindVariable<Light>("light", scene->objects->at("light1"));
        shader->bindVariable("reflection", 100);
        shader->bindVariable("shadowBias", glm::mat4x4(0.5, 0, 0, 0,
                                                       0, 0.5, 0, 0,
                                                       0, 0, 0.5, 0,
                                                       0.5, 0.5, 0.5, 1.0));
        shader->bindVariable("depth_viewTransform", glm::lookAt(scene->get<Light>("light1")->getPosition(), glm::vec3(0,0,0), glm::vec3(0,1,0)));
        shader->bindVariable("depth_projectionTransform", scene->cameras->at("main")->getProjectionMatrix(ProjectionType::ORTHOGRAPHIC, -10.0f, 10.0f, 10.0f, -10.0f, -10.0f, 20.0f));
        
    };

    scene->objects->insert({"Cube1", new GLObject(Cube::getInstance())});
    scene->get<GLObject>("Cube1")->textures->push_back(TextureManager::getInstance()->loadTexture<BMPTexture>("crate", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/crate.bmp"));
    scene->get<GLObject>("Cube1")->setProgram(lightingShader);
    scene->get<GLObject>("Cube1")->scaleLocal(.5, .5, .5);
    
 
    
    scene->objects->insert({"Plane1", new GLObject(RectangularPlane::getInstance())});
    scene->get<GLObject>("Plane1")->textures->push_back(TextureManager::getInstance()->loadTexture<BMPTexture>("ground", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/wood_flooring.bmp"));
    scene->get<GLObject>("Plane1")->setProgram(lightingShader);
    scene->get<GLObject>("Plane1")->scaleLocal(5, 5, 5);
    scene->get<GLObject>("Plane1")->rotateLocal(M_PI / 2, 0, 0);
    scene->get<GLObject>("Plane1")->translateGlobal(0, -.501, -.53f);
    
    scene->objects->insert({"light1", new Light()});
    scene->get<Light>("light1")->translateGlobal(0, 0, 2);
    //scene->get<Light>("light1")->rotateLocal(-M_PI / 4.0, 0, 0);
    scene->get<Light>("light1")->attachScript<Spin>("lightMvmnt");
    
    
    scene->cameras->at("main")->translateGlobal(0, 0, -2.1);
    scene->cameras->at("main")->attachScript<BasicMovement>("movement");
    scene->attachScript<BloomScript>("bloomControl");
    SceneManager::getInstance()->scenes->insert({"main", scene});
    system->start();
}




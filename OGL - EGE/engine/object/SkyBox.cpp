//
//  SkyBox.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/11/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "SkyBox.hpp"
#include "Cube.hpp"
#include "TextureManager.hpp"
#include "ShaderManager.hpp"
#include "Scene.hpp"

static int skyBoxCount = 0;


SkyBox::SkyBox(std::string path): GLObject() {
    this->geometry = new Cube();
    this->geometry->updateUVs(new GLfloat[72] {
        0.25, 1.0 / 3.0,
        0.5, 2.0 / 3.0,
        0.25, 2.0 / 3.0,
        0.25, 1.0 / 3.0,
        0.5, 1.0 / 3.0,
        0.5, 2.0 / 3.0,

        1.0, 1.0 / 3.0,
        0.75, 2.0 / 3.0,
        1.0, 2.0 / 3.0,
        1.0, 1.0 / 3.0,
        0.75, 1.0 / 3.0,
        0.75, 2.0 / 3.0,

        0, 1.0 / 3.0,
        0.25, 2.0 / 3.0,
        0, 2.0 / 3.0,
        0, 1.0 / 3.0,
        0.25, 1.0 / 3.0,
        0.25, 2.0 / 3.0,

        0.75, 1.0 / 3.0,
        0.5, 2.0 / 3.0,
        0.75, 2.0 / 3.0,
        0.75, 1.0 / 3.0,
        0.5, 1.0 / 3.0,
        0.5, 2.0 / 3.0,

        
        0.25f, 2.0f / 3.0f,
        0.5f, 1.0f,
        0.25f, 1.0f,
        0.25f, 2.0f / 3.0f,
        0.5f, 2.0f / 3.0f,
        0.5f, 1.0f,
        
        0.25, 0,
        0.5, 1.0 / 3.0,
        0.25, 1.0 / 3.0,
        0.25, 0,
        0.5, 0,
        0.5, 1.0 / 3.0
    }, 72);
    this->textures->push_back(TextureManager::getInstance()->loadTexture<BMPTexture>("skybox_" + std::to_string(skyBoxCount++), path));
    ShaderProgram * shader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/skybox_single.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/skybox_single.fragment.glsl");
    
    shader->bindVars = [](GLObject* obj, Scene* scene) {
        obj->shader->bindVariable("modelTransform", obj->getModelMatrix());
        // add bind camera function
        obj->shader->bindVariable("viewTransform", scene->cameras->at("main")->getScaleRotationMatrix());
        obj->shader->bindVariable("projectionTransform", scene->cameras->at("main")->getProjectionMatrix());
        obj->shader->bindVariable<Texture>("tex", obj->textures->at(0));
    };
    this->setProgram(shader);
    this->scaleLocal(100, 100, 100);
}


SkyBox::SkyBox(std::string l, std::string f, std::string r, std::string b, std::string t, std::string btm) {
    this->textures->push_back(TextureManager::getInstance()->loadCubeMap("skybox_" + std::to_string(skyBoxCount++), l, f, r, b, t, btm));
    this->geometry = new Cube();

    ShaderProgram * shader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/skybox.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/skybox.fragment.glsl");
    
    shader->bindVars = [](GLObject* obj, Scene* scene) {
        obj->shader->bindVariable("modelTransform", obj->getModelMatrix());
        // add bind camera function
        obj->shader->bindVariable("viewTransform", scene->cameras->at("main")->getScaleRotationMatrix());
        obj->shader->bindVariable("projectionTransform", scene->cameras->at("main")->getProjectionMatrix());
        obj->shader->bindVariable<CubeMap>("tex", obj->textures->at(0));
    };
    this->setProgram(shader);
    this->scaleLocal(100, 100, 100);

}

void SkyBox::render(Scene* scene, ShaderProgram* program) {
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
    GLObject::render(scene);
    glEnable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);

}



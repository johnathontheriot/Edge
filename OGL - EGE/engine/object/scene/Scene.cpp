//
//  Scene.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Scene.hpp"
#include <unordered_map>
#include "../Camera.hpp"
#include "../GLObject.hpp"
#include "Script.hpp"
#include "System.hpp"

Scene::Scene(GLFWwindow * window) {
    this->effectsPipeline = new std::list<PostProcessor*>;
    this->imageEffects = new std::list<PostProcessor*>;
    Dimensions d = System::getInstance()->getWindowDimenions(window);
    this->cameras = new std::unordered_map<std::string, Camera*>();
    this->objects = new std::unordered_map<std::string, IGLObject*>();
    this->viewPort = new Dimensions(d.width, d.height);
    this->cameras->insert({"main", new Camera(45.0f, d.width / d.height, 0.1f, 1000.0f, - (d.width / d.width), (d.width / d.width), (d.height / d.width), - (d.height / d.width))});
}



void Scene::render() {
    for (std::list<PostProcessor*>::iterator it = this->effectsPipeline->begin(); it != this->effectsPipeline->end(); ++it) {
        (*it)->render(this, this->viewPort, this->objects);
    }
    for (std::list<PostProcessor*>::iterator it = this->imageEffects->begin(); it != this->imageEffects->end(); ++it) {
        (*it)->render(this, this->viewPort, this->objects);
    }
    if (this->imageEffects->size() == 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for( std::unordered_map<std::string, IGLObject*>::const_iterator it = this->objects->begin(); it != this->objects->end(); ++it ) {
            it->second->render(this);
        }
    }
}


void Scene::tick() {
    IScriptable::tick();
    for (std::unordered_map<std::string, IGLObject*>::const_iterator it = this->objects->begin(); it != this->objects->end(); ++it) {
        ((IScriptable*)it->second)->tick();
    }
    for (std::unordered_map<std::string, Camera*>::const_iterator it = this->cameras->begin(); it != this->cameras->end(); ++it) {
        it->second->tick();
    }
}

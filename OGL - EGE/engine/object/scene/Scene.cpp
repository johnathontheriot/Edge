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
    Dimensions d = System::getInstance()->getWindowDimenions(window);
    this->cameras = new std::unordered_map<std::string, Camera*>();
    this->objects = new std::unordered_map<std::string, GLObject*>();
    this->scripts = new std::unordered_map<std::string, Script<Scene>*>();
    this->cameras->insert({"main", new Camera(45.0f, d.width / d.height, 0.1f, 1000.0f)});
}



void Scene::render() {
    for( std::unordered_map<std::string, GLObject*>::const_iterator it = this->objects->begin(); it != this->objects->end(); ++it ) {
        it->second->render(this);
    }
}

template <class ScriptType> void Scene::attachScript(std::string name) {
    ScriptType * script = new ScriptType();
    this->scripts->insert({name, script});
}

void Scene::tick() {
    for (std::unordered_map<std::string, Script<Scene>*>::const_iterator it = this->scripts->begin(); it != this->scripts->end(); ++it) {
        it->second->tick(this);
    }
    for (std::unordered_map<std::string, GLObject*>::const_iterator it = this->objects->begin(); it != this->objects->end(); ++it) {
        it->second->tick();
    }
}

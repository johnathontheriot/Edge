//
//  Scene.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Scene.hpp"
#include <unordered_map>
#include "Camera.hpp"
#include "GLObject.hpp"

Scene::Scene() {
    this->cameras = new std::unordered_map<std::string, Camera*>();
    this->objects = new std::unordered_map<std::string, GLObject*>();
    this->cameras->insert({"main", new Camera()});
}

void Scene::render() {
    for( std::unordered_map<std::string, GLObject*>::const_iterator it = this->objects->begin(); it != this->objects->end(); ++it ) {
        it->second->render(this);
    }
}

//
//  TextBox.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/10/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "TextBox.hpp"
#include "RectangularPlane.hpp"
#include <regex>
#include "DDSTexture.hpp"
#include "TextureManager.hpp"
#include "ShaderManager.hpp"

void TextBox::changeText(std::string newText) {
    //todo
}

TextBox::TextBox(std::string text): GLObject() {
    // this will be parameterized - need to create a a devoted shader for text
    this->textures->push_back(TextureManager::getInstance()->loadTexture<DDSTexture>("glyph1", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/Holstein.DDS"));
    ShaderProgram * shader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/solid.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/solid.fragment.glsl");
    
    shader->bindVars = [](GLObject* obj, Scene* scene) {
        obj->shader->bind4fMatrix("modelTransform", obj->getModelMatrix());
        // add bind camera function
        obj->shader->bind4fMatrix("viewTransform", scene->cameras->at("main")->getViewMatrix());
        obj->shader->bind4fMatrix("projectionTransform", scene->cameras->at("main")->getProjectionMatrix());
        obj->shader->bindTexture("tex", obj->textures->at(0));
    };
    this->setProgram(shader);
    // End changes
    this->text = text;
    GLfloat * uvs = new GLfloat[12 * text.length()];
    for(int i = 0; i < text.length(); i++) {
        this->getCharacter(text[i], &uvs[i * 12]);
    }
    this->geometry = new RectangularPlane(1, (int)text.length(), uvs);
    this->scaleLocal(text.length(), 1, 1);
}

void TextBox::getCharacter(int character, GLfloat* uvs) {
    GLfloat deltaU = (1.0f / 16.0f);
    GLfloat deltaV = (1.0f / 16.0f);
    GLfloat u = (character % 16) * deltaU;
    GLfloat v = 1 - (((character / 16) + 1) * deltaV);
    uvs[0] = u;
    uvs[1] = v;
    uvs[2] = u + deltaU;
    uvs[3] = v + deltaV;
    uvs[4] = u;
    uvs[5] = v + deltaV;
    uvs[6] = u;
    uvs[7] = v;
    uvs[8] = u + deltaU;
    uvs[9] = v;
    uvs[10] = u + deltaU;
    uvs[11] = v + deltaV;
}

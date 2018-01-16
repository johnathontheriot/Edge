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
#include "TextureManager.hpp"
#include "ShaderManager.hpp"
#include "Utilities.hpp"

void TextBox::changeText(std::string newText) {
    //todo
}


TextBox::TextBox(std::string text, int color): GLObject() {
    // this will be parameterized - need to create a a devoted shader for text
    this->textures->push_back(TextureManager::getInstance()->loadTexture<DDSTexture>("glyph1", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/Holstein.DDS"));
    ShaderProgram * shader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/basic_text.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/basic_text.fragment.glsl");
    
    shader->bindVars = [this](GLObject* obj, Scene* scene) {
        obj->shader->bindVariable("modelTransform", obj->getModelMatrix());
        // add bind camera function
        obj->shader->bindVariable("viewTransform", scene->cameras->at("main")->getViewMatrix());
        obj->shader->bindVariable("projectionTransform", scene->cameras->at("main")->getProjectionMatrix());
        obj->shader->bindVariable<Texture>("tex", obj->textures->at(0));
        obj->shader->bindVariable("textColor", this->color);
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
    this->color = Utilities::toColor(color);
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

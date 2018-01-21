//
//  TextBox.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/10/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef TextBox_hpp
#define TextBox_hpp

#include <stdio.h>
#include "GLObject.hpp"
#include <glm/vec4.hpp>

class TextBox: public GLObject {
private:
    std::string text;
    glm::vec4 color;
public:
    template <class ScriptType>
    void attachScript(std::string name) {
        IScriptable::attachScript<ScriptType, TextBox>(name);
    }
    void changeText(std::string);
    TextBox(std::string, int = 0xFFFFFFFF);
    void getCharacter(int, GLfloat*);
    void render(Scene* scene, ShaderProgram* program = NULL) {
        glEnable(GL_BLEND);
        glDisable(GL_CULL_FACE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLObject::render(scene, program);
        glEnable(GL_CULL_FACE);
        glDisable(GL_BLEND);
    }
};

#endif /* TextBox_hpp */

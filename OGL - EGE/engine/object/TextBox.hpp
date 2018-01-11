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


class TextBox: public GLObject {
private:
    std::string text;
public:
    void changeText(std::string);
    TextBox(std::string);
    void getCharacter(int, GLfloat*);
    void render(Scene* scene) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLObject::render(scene);
        glDisable(GL_BLEND);
    }
};

#endif /* TextBox_hpp */

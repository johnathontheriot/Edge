//
//  CubeMap.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/12/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "CubeMap.hpp"


CubeMap::CubeMap(Texture* l, Texture* f, Texture* r, Texture* b, Texture* t, Texture* bm) {
    this->left = l;
    this->right = r;
    this->front = f;
    this->back = b;
    this->top = t;
    this->bottom = bm;
}



void CubeMap::bind(int txEnum, int txIdx) {
    GLuint textureID;
    this->texEnum = txEnum;
    this->texIndex = txIdx;
    glActiveTexture(this->texEnum);
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);
    
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, this->right->width, this->right->height, 0, GL_BGR, GL_UNSIGNED_BYTE, this->right->data);
    
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, this->left->width, this->left->height, 0, GL_BGR, GL_UNSIGNED_BYTE, this->left->data);
    
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, this->top->width, this->top->height, 0, GL_BGR, GL_UNSIGNED_BYTE, this->top->data);
    
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, this->bottom->width, this->bottom->height, 0, GL_BGR, GL_UNSIGNED_BYTE, this->bottom->data);
    
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, this->back->width, this->back->height, 0, GL_BGR, GL_UNSIGNED_BYTE, this->back->data);
    
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, this->front->width, this->front->height, 0, GL_BGR, GL_UNSIGNED_BYTE, this->front->data);

}

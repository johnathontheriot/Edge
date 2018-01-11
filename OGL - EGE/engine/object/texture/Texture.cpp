//
//  Texture.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Texture.hpp"

Texture::Texture(int width, int height, unsigned char * data) {
    this->width = width;
    this->height = height;
    this->data = data;
}

Texture::Texture() {
    
}

void Texture::bind() {
    
}

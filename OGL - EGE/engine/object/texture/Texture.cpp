//
//  Texture.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Texture.hpp"

Texture::Texture(GLuint id, ImageData * imageProperties) {
    this->id = id;
    this->imageProperties = imageProperties;
}

Texture::Texture() {
    
}

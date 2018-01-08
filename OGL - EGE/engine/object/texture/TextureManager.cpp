//
//  TextureManager.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include <string>
#include <sstream>
#include <iostream>
#include "TextureManager.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

TextureManager * TextureManager::Instance;


TextureManager * TextureManager::getInstance() {
    if (!TextureManager::Instance) {
        TextureManager::Instance = new TextureManager();
    }
    return TextureManager::Instance;
}



TextureManager::TextureManager() {
    this->textures = new std::unordered_map<std::string, Texture *>();
}

// Adapted from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
ImageData TextureManager::loadBMP(const char * path) {
    unsigned char header[54];
    FILE * file = fopen(path,"rb");
    if (!file || fread(header, 1, 54, file) != 54 ||  header[0] != 'B' || header[1] != 'M'){
        return ImageData(0, 0, NULL, "bpm");
    }
    unsigned int dataPos    = *(int*)&(header[0x0A]);
    unsigned int imageSize  = *(int*)&(header[0x22]);
    unsigned int width      = *(int*)&(header[0x12]);
    unsigned int height     = *(int*)&(header[0x16]);
    if (imageSize == 0) {
        imageSize = width * height * 3;
    }
    if (dataPos == 0) {
        dataPos = 54;
    }
    unsigned char * data = new unsigned char [imageSize];
    fread(data, 1, imageSize, file);
    fclose(file);
    return ImageData(width, height, data, "bmp");
}

Texture * TextureManager::loadTexture(std::string name, std::string path) {
    return this->loadTexture(name, TextureManager::loadBMP(path.c_str()));
}

Texture * TextureManager::loadTexture(std::string name, ImageData imageProps) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, imageProps.width, imageProps.height, 0, GL_BGR, GL_UNSIGNED_BYTE, imageProps.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    Texture * tex = new Texture(textureID, &imageProps);
    this->textures->insert({name, tex});
    return tex;
}







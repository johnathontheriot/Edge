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
int TextureManager::textureNumber = 0;
int TextureManager::textureEnum = GL_TEXTURE0;

TextureManager * TextureManager::getInstance() {
    if (!TextureManager::Instance) {
        TextureManager::Instance = new TextureManager();
    }
    return TextureManager::Instance;
}

template<> BMPTexture * TextureManager::loadImage<BMPTexture>(const char * path){
    unsigned char header[54];
    FILE * file = fopen(path,"rb");
    if (!file || fread(header, 1, 54, file) != 54 ||  header[0] != 'B' || header[1] != 'M'){
        return NULL;
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
    return new BMPTexture(width, height, data);
}

TextureManager::TextureManager() {
    this->textures = new std::unordered_map<std::string, Texture *>();
}

// Adapted from http://www.opengl-tutorial.org
template<> DDSTexture * TextureManager::loadImage<DDSTexture>(const char * path){
    unsigned char header[124];
    
    FILE *fp = fopen(path, "rb");
    if (fp == NULL){
        return NULL;
    }
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return NULL;
    }
    fread(&header, 124, 1, fp);
    unsigned int height = *(unsigned int*)&(header[8 ]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);
    unsigned int bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    unsigned char * buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    fclose(fp);
    
    unsigned int format;
    switch(fourCC)
    {
        case 0x31545844:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case 0x33545844:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case 0x35545844:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            //free(buffer);
            return NULL;
    }
    return new DDSTexture(width, height, format, mipMapCount, buffer);
}

Texture * TextureManager::loadTexture(std::string name, std::string path) {
    if (path.substr(path.find_last_of(".") + 1) == "bmp") {
        return this->loadTexture<BMPTexture>(name, path);
    }
    else if (path.substr(path.find_last_of(".") + 1) == "DDS") {
        return this->loadTexture<DDSTexture>(name, path);
    }
    return NULL;
}

Texture * TextureManager::loadCubeMap(std::string name, std::string l, std::string f, std::string r, std::string b, std::string t, std::string bm) {
    Texture * lt = TextureManager::loadTexture(name + " left", l);
    Texture * ft = TextureManager::loadTexture(name + " front", f);
    Texture * rt = TextureManager::loadTexture(name + " right", r);
    Texture * bt = TextureManager::loadTexture(name + " back", b);
    Texture * tt = TextureManager::loadTexture(name + " top", t);
    Texture * bmt = TextureManager::loadTexture(name + " bottom", bm);
    CubeMap * texture = new CubeMap(lt, ft, rt, bt, tt, bmt);
    texture->bind(TextureManager::textureEnum++, TextureManager::textureNumber++);
    this->textures->insert({name, texture});
    return texture;
}








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
#include "DDSTexture.hpp"

TextureManager * TextureManager::Instance;


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
    int a = fread(data, 1, imageSize, file);
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
    
    unsigned int components  = (fourCC == 0x31545844) ? 3 : 4;
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










//
//  DDSTexture.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/10/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "DDSTexture.hpp"
#include <string>
#include <sstream>
#include <iostream>

void DDSTexture::bind() {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;
    
    for (unsigned int level = 0; level < this->mipMapCount && (this->width || this->height); ++level)
    {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, this->format, this->width, this->height,
                               0, size, this->data + offset);
        
        offset += size;
        width /= 2;
        height /= 2;
        if(width < 1) {
            width = 1;
        }
        if(height < 1) {
             height = 1;
        }
        
    }
    
    //free(this->data);
//    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, this->width, this->height, 0, GL_BGR, GL_UNSIGNED_BYTE, this->data);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    this->id = textureID;
}

DDSTexture::DDSTexture(int width, int height, int format, int mipMapCount, unsigned char * data): Texture(width, height, data) {
    this->format = format;
    this->mipMapCount = mipMapCount;
}

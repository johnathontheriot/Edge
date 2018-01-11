//
//  RectangularPlane.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/10/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "RectangularPlane.hpp"

void RectangularPlane::generateVertices(GLfloat * uvs) {
    GLfloat deltaX = 2.0f / this->columns;
    GLfloat deltaY = 2.0f / this->rows;
    int numSections = (this->rows) * (this->columns);
    this->vertexBuffer = new GLfloat[numSections * 18];
    this->uvBuffer = new GLfloat[numSections * 12];
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->columns; col++) {
            int filledSpaceV = (row * this->columns * 18) + (col * 18);
            int filleSpaceUV = (row * this->columns * 12) + (col * 12);
            this->vertexBuffer[filledSpaceV] = - 1.0f + (col * deltaX);
            this->vertexBuffer[filledSpaceV + 1] = 1.0f - ((row + 1.0f) * deltaY);
            this->vertexBuffer[filledSpaceV + 2] = 0.0f;
            this->uvBuffer[filleSpaceUV] = uvs ? uvs[filleSpaceUV] : (col * deltaX * 0.5f);
            this->uvBuffer[filleSpaceUV + 1] = uvs ? uvs[filleSpaceUV + 1] : 1.0f - ((row + 1.0f) * deltaY * 0.5f);
            
            this->vertexBuffer[filledSpaceV + 3] = - 1.0f + ((col + 1.0f) * deltaX);
            this->vertexBuffer[filledSpaceV + 4] = 1.0f - (row * deltaY);
            this->vertexBuffer[filledSpaceV + 5] = 0.0f;
            this->uvBuffer[filleSpaceUV + 2] = uvs ? uvs[filleSpaceUV + 2] : ((col + 1.0f) * deltaX * 0.5f);
            this->uvBuffer[filleSpaceUV + 3] = uvs ? uvs[filleSpaceUV + 3] : 1.0f - (row * deltaY * 0.5f);
            
            this->vertexBuffer[filledSpaceV + 6] = - 1.0f + (col * deltaX);
            this->vertexBuffer[filledSpaceV + 7] = 1.0f - (row * deltaY);
            this->vertexBuffer[filledSpaceV + 8] = 0.0f;
            this->uvBuffer[filleSpaceUV + 4] = uvs ? uvs[filleSpaceUV + 4] : (col * deltaX) * 0.5f;
            this->uvBuffer[filleSpaceUV + 5] = uvs ? uvs[filleSpaceUV + 5] : 1.0f - (row * deltaY * 0.5f);
            
            this->vertexBuffer[filledSpaceV + 9] =  - 1.0f + (col * deltaX);
            this->vertexBuffer[filledSpaceV + 10] =  1.0f - ((row + 1.0f) * deltaY);
            this->vertexBuffer[filledSpaceV + 11] = 0.0f;
            this->uvBuffer[filleSpaceUV + 6] = uvs ? uvs[filleSpaceUV + 6] : (col * deltaX * 0.5f);
            this->uvBuffer[filleSpaceUV + 7] = uvs ? uvs[filleSpaceUV + 7] : 1.0f - ((row + 1.0f) * deltaY * 0.5f);
            
            this->vertexBuffer[filledSpaceV + 12] =  - 1.0f + ((col + 1.0f) * deltaX);
            this->vertexBuffer[filledSpaceV + 13] =  1.0f - ((row + 1.0f) * deltaY);
            this->vertexBuffer[filledSpaceV + 14] = 0.0f;
            this->uvBuffer[filleSpaceUV + 8] = uvs ? uvs[filleSpaceUV + 8] : ((col + 1.0f) * deltaX * 0.5f);
            this->uvBuffer[filleSpaceUV + 9] = uvs ? uvs[filleSpaceUV + 9] : 1.0f - ((row + 1.0f) * deltaY * 0.5f);
            
            this->vertexBuffer[filledSpaceV + 15] = - 1.0f + ((col + 1.0f) * deltaX);
            this->vertexBuffer[filledSpaceV + 16] = 1.0f - (row * deltaY);
            this->vertexBuffer[filledSpaceV + 17] = 0.0f;
            this->uvBuffer[filleSpaceUV + 10] = uvs ? uvs[filleSpaceUV + 10] : ((col + 1.0f) * deltaX * 0.5f);
            this->uvBuffer[filleSpaceUV + 11] = uvs ? uvs[filleSpaceUV + 11] : 1.0f - (row * deltaY * 0.5f);
        }
    }
    
    this->colorBuffer =  vertexBuffer;
    this->vertexBufferSize = numSections * 18;
}


RectangularPlane::RectangularPlane(int rows, int cols) {
    this->rows = rows;
    this->columns = cols;
    this->generateVertices(NULL);
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->createBuffer(this->VBOid);
    this->createBuffer(this->UVOid);
    this->createBuffer(this->CBOid);
    this->bindBuffers();
}

RectangularPlane::RectangularPlane(int rows, int cols, GLfloat* uvs) {
    this->rows = rows;
    this->columns = cols;
    this->generateVertices(uvs);
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->createBuffer(this->VBOid);
    this->createBuffer(this->UVOid);
    this->createBuffer(this->CBOid);
    this->bindBuffers();
}


RectangularPlane * RectangularPlane::Instance;


RectangularPlane::RectangularPlane(): Geometry(){
    this->vertexBuffer = new GLfloat[18] {
        //front
        -1, -1, 0,
        1, 1, 0,
        -1, 1, 0,
        -1, -1, 0,
        1, -1, 0,
        1, 1, 0
    };
    this->colorBuffer =  vertexBuffer;
    
    
    this->uvBuffer = new GLfloat[12] {
        0, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1
    };
    this->vertexBufferSize = 18;
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->createBuffer(this->VBOid);
    this->createBuffer(this->UVOid);
    this->createBuffer(this->CBOid);
    this->bindBuffers();
}

RectangularPlane * RectangularPlane::getInstance() {
    if (!RectangularPlane::Instance) {
        RectangularPlane::Instance = new RectangularPlane();
    }
    return RectangularPlane::Instance;
}

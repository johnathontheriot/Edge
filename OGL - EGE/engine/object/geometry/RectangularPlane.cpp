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
    GLfloat * vertices = new GLfloat[numSections * 18];
    GLfloat * uvBuffer = new GLfloat[numSections * 12];
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->columns; col++) {
            int filledSpaceV = (row * this->columns * 18) + (col * 18);
            int filleSpaceUV = (row * this->columns * 12) + (col * 12);
            vertices[filledSpaceV] = - 1.0f + (col * deltaX);
            vertices[filledSpaceV + 1] = 1.0f - ((row + 1.0f) * deltaY);
            vertices[filledSpaceV + 2] = 0.0f;
            uvBuffer[filleSpaceUV] = uvs ? uvs[filleSpaceUV] : (col * deltaX * 0.5f);
            uvBuffer[filleSpaceUV + 1] = uvs ? uvs[filleSpaceUV + 1] : 1.0f - ((row + 1.0f) * deltaY * 0.5f);
            
            vertices[filledSpaceV + 3] = - 1.0f + ((col + 1.0f) * deltaX);
            vertices[filledSpaceV + 4] = 1.0f - (row * deltaY);
            vertices[filledSpaceV + 5] = 0.0f;
            uvBuffer[filleSpaceUV + 2] = uvs ? uvs[filleSpaceUV + 2] : ((col + 1.0f) * deltaX * 0.5f);
            uvBuffer[filleSpaceUV + 3] = uvs ? uvs[filleSpaceUV + 3] : 1.0f - (row * deltaY * 0.5f);
            
            vertices[filledSpaceV + 6] = - 1.0f + (col * deltaX);
            vertices[filledSpaceV + 7] = 1.0f - (row * deltaY);
            vertices[filledSpaceV + 8] = 0.0f;
            uvBuffer[filleSpaceUV + 4] = uvs ? uvs[filleSpaceUV + 4] : (col * deltaX) * 0.5f;
            uvBuffer[filleSpaceUV + 5] = uvs ? uvs[filleSpaceUV + 5] : 1.0f - (row * deltaY * 0.5f);
            
            vertices[filledSpaceV + 9] =  - 1.0f + (col * deltaX);
            vertices[filledSpaceV + 10] =  1.0f - ((row + 1.0f) * deltaY);
            vertices[filledSpaceV + 11] = 0.0f;
            uvBuffer[filleSpaceUV + 6] = uvs ? uvs[filleSpaceUV + 6] : (col * deltaX * 0.5f);
            uvBuffer[filleSpaceUV + 7] = uvs ? uvs[filleSpaceUV + 7] : 1.0f - ((row + 1.0f) * deltaY * 0.5f);
            
            vertices[filledSpaceV + 12] =  - 1.0f + ((col + 1.0f) * deltaX);
            vertices[filledSpaceV + 13] =  1.0f - ((row + 1.0f) * deltaY);
            vertices[filledSpaceV + 14] = 0.0f;
            uvBuffer[filleSpaceUV + 8] = uvs ? uvs[filleSpaceUV + 8] : ((col + 1.0f) * deltaX * 0.5f);
            uvBuffer[filleSpaceUV + 9] = uvs ? uvs[filleSpaceUV + 9] : 1.0f - ((row + 1.0f) * deltaY * 0.5f);
            
            vertices[filledSpaceV + 15] = - 1.0f + ((col + 1.0f) * deltaX);
            vertices[filledSpaceV + 16] = 1.0f - (row * deltaY);
            vertices[filledSpaceV + 17] = 0.0f;
            uvBuffer[filleSpaceUV + 10] = uvs ? uvs[filleSpaceUV + 10] : ((col + 1.0f) * deltaX * 0.5f);
            uvBuffer[filleSpaceUV + 11] = uvs ? uvs[filleSpaceUV + 11] : 1.0f - (row * deltaY * 0.5f);
        }
    }
    if (this->buffers->find("vertex") ==  this->buffers->end()) {
        this->buffers->insert({"vertex", new GLBufferObject<GLfloat>(this->bufferListSize++, 3, GL_FLOAT, numSections * 18, vertices)});
        //this->buffers->insert({"colors", new GLBufferObject<GLfloat>(this->bufferListSize++, 3, GL_FLOAT, numSections * 18, vertices)});

    }
    else {
        this->updateVertices(vertices, numSections * 18);
    }
    
    if (this->buffers->find("uvs") ==  this->buffers->end()) {
        this->buffers->insert({"uvs", new GLBufferObject<GLfloat>(this->bufferListSize++, 2, GL_FLOAT, numSections * 12, uvBuffer)});
    }
    else {
        this->updateUVs(uvBuffer, numSections * 12);
    }

}


RectangularPlane::RectangularPlane(int rows, int cols) {
    this->buffers = new std::unordered_map<std::string, BufferObject*>();
    this->rows = rows;
    this->columns = cols;
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->generateVertices(NULL);
    this->bindBuffers();
    this->generateFaceNormals();
}

RectangularPlane::RectangularPlane(int rows, int cols, GLfloat* uvs) {
    this->buffers = new std::unordered_map<std::string, BufferObject*>();
    this->rows = rows;
    this->columns = cols;
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->generateVertices(uvs);
    this->bindBuffers();
    this->generateFaceNormals();
}


RectangularPlane * RectangularPlane::Instance;


RectangularPlane::RectangularPlane(): Geometry(){
    this->buffers = new std::unordered_map<std::string, BufferObject*>();

    GLfloat * vertices = new GLfloat[36] {
        //front
        -1, 1, 0,
        -1, -1, 0,
        1, -1, 0,
        1, -1, 0,
        1, 1, 0,
        -1, 1, 0,
        
        -1, 1, 0.0001f,
        1, 1, 0.0001f,
        1, -1, 0.0001f,
        1, -1, 0.0001f,
        -1, -1, 0.0001f,
        -1, 1, 0.0001f
    };
    
    GLfloat * uvBuffer = new GLfloat[24] {
        0, 1,
        0, 0,
        1, 0,
        1, 0,
        1, 1,
        0, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 0,
        1, 1,
        0, 1
    };
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->buffers->insert({"vertex", new GLBufferObject<GLfloat>(this->bufferListSize++, 3, GL_FLOAT, 36, vertices)});
    this->buffers->insert({"uvs", new GLBufferObject<GLfloat>(this->bufferListSize++, 2, GL_FLOAT, 24, uvBuffer)});
    //this->buffers->insert({"colors", new GLBufferObject<GLfloat>(this->bufferListSize++, 3, GL_FLOAT, 18, vertices)});

    this->bindBuffers();
    this->generateFaceNormals();

}

RectangularPlane * RectangularPlane::getInstance() {
    if (!RectangularPlane::Instance) {
        RectangularPlane::Instance = new RectangularPlane();
    }
    return RectangularPlane::Instance;
}

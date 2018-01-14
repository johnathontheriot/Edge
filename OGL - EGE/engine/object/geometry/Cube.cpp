//
//  Cube.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Cube.hpp"

Cube * Cube::Instance;


Cube::Cube(): Geometry(){
    GLfloat * vertices = new GLfloat[108] {
        //front
        -1, -1, 1,
        1, 1, 1,
        -1, 1, 1,
        -1, -1, 1,
        1, -1, 1,
        1, 1, 1,
        //back
        -1, -1, -1,
        1, 1, -1,
        -1, 1, -1,
        -1, -1, -1,
        1, -1, -1,
        1, 1, -1,
        //left
        -1, -1, -1,
        -1, 1, 1,
        -1, 1, -1,
        -1, -1, -1,
        -1, -1, 1,
        -1, 1, 1,
        //right
        1, -1, -1,
        1, 1, 1,
        1, 1, -1,
        1, -1, -1,
        1, -1, 1,
        1, 1, 1,
        //top
        -1, 1, 1,
        1, 1, -1,
        -1, 1, -1,
        -1, 1, 1,
        1, 1, 1,
        1, 1, -1,
        //bottom
        -1, -1, 1,
        1, -1, -1,
        -1, -1, -1,
        -1, -1, 1,
        1, -1, 1,
        1, -1, -1
    };

    this->buffers = new std::unordered_map<std::string, BufferObject*>();


    
    GLfloat * uvs = new GLfloat[72] {
        0, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1,
        0, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1,
        0, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1,
        0, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1,
        0, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1,
        0, 0,
        1, 1,
        0, 1,
        0, 0,
        1, 0,
        1, 1
    };
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->buffers->insert({"vertex", new GLBufferObject<GLfloat>(this->bufferListSize++, 3, GL_FLOAT, 108, vertices)});
    this->buffers->insert({"uvs", new GLBufferObject<GLfloat>(this->bufferListSize++, 2, GL_FLOAT, 72, uvs)});
    //this->buffers->insert({"colors", new GLBufferObject<GLfloat>(this->bufferListSize++, 3, GL_FLOAT, 108, vertices)});

    this->bindBuffers();
}

Cube * Cube::getInstance() {
    if (!Cube::Instance) {
        Cube::Instance = new Cube();
    }
    return Cube::Instance;
}


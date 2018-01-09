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
    this->vertexBuffer = new GLfloat[108] {
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
    this->colorBuffer =  vertexBuffer;

    
    this->uvBuffer = new GLfloat[72] {
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
    this->vertexBufferSize = 108;
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->createBuffer(this->VBOid);
    this->bindBuffer<GLfloat>(this->VBOid, this->vertexBuffer, this->vertexBufferSize);
    this->createBuffer(this->UVOid);
    this->bindBuffer<GLfloat>(this->UVOid, this->uvBuffer, (this->vertexBufferSize / 3) * 2);
    this->createBuffer(this->CBOid);
    this->bindBuffer<GLfloat>(this->CBOid, this->colorBuffer, this->vertexBufferSize);
}

Cube * Cube::getInstance() {
    if (!Cube::Instance) {
        Cube::Instance = new Cube();
    }
    return Cube::Instance;
}

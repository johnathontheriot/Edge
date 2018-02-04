//
//  Sphere.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 2/3/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Sphere.hpp"

Sphere * Sphere::Instance;


Sphere::Sphere(int xRotations, int zRotations): Geometry(){
    int numVertices = (((zRotations - 2) * 2) + 2) * xRotations * 3 * 3;
    int numUVs = (((zRotations - 2) * 2) + 2) * xRotations * 3 * 2;
    GLfloat * vertices = new GLfloat[numVertices]{0.0f};
    GLfloat * uvs = new GLfloat[numUVs]{0.0f};
    GLfloat deltaX = (2.0f * M_PI) / xRotations;
    GLfloat deltaZ = (M_PI) / zRotations;
    int currentVertex = 0;
    int currentUV = 0;

    for (float horizontalStrip = 0; horizontalStrip < xRotations; horizontalStrip++) {
        vertices[currentVertex++] = 1.0f;
        vertices[currentVertex++] = 0.0f;
        vertices[currentVertex++] = 0.0f;
        uvs[currentUV++] = horizontalStrip / zRotations;
        uvs[currentUV++] = 1.0f;
        vertices[currentVertex++] = cos(deltaZ);
        vertices[currentVertex++] = sin((horizontalStrip + 1) * deltaX) * sin(deltaZ);
        vertices[currentVertex++] = cos((horizontalStrip + 1) * deltaX) * sin(deltaZ);
        uvs[currentUV++] = horizontalStrip / zRotations;
        uvs[currentUV++] = (xRotations - (1.0f / xRotations))/ xRotations;
        vertices[currentVertex++] = cos(deltaZ);
        vertices[currentVertex++] = sin(horizontalStrip * deltaX) * sin(deltaZ);
        vertices[currentVertex++] = cos(horizontalStrip * deltaX) * sin(deltaZ);
        uvs[currentUV++] = horizontalStrip / zRotations;
        uvs[currentUV++] = (xRotations - (1.0f / xRotations))/ xRotations;
        for (float cell = 1.0f; cell < zRotations - 1; cell++) {
            vertices[currentVertex++] = cos(cell * deltaZ);
            vertices[currentVertex++] = sin(horizontalStrip * deltaX) * sin(cell * deltaZ);
            vertices[currentVertex++] = cos(horizontalStrip * deltaX) * sin(cell * deltaZ);
            uvs[currentUV++] = horizontalStrip / xRotations;
            uvs[currentUV++] = cell / zRotations;
            vertices[currentVertex++] = cos(cell * deltaZ);
            vertices[currentVertex++] = sin((horizontalStrip + 1) * deltaX) * sin(cell *deltaZ);
            vertices[currentVertex++] = cos((horizontalStrip + 1) * deltaX) * sin(cell *deltaZ);
            uvs[currentUV++] = (horizontalStrip + 1.0f) / xRotations;
            uvs[currentUV++] = (cell) / zRotations;
            vertices[currentVertex++] = cos((cell + 1) * deltaZ);
            vertices[currentVertex++] = sin(horizontalStrip * deltaX) * sin( (cell + 1) * deltaZ);
            vertices[currentVertex++] = cos(horizontalStrip * deltaX) * sin( (cell + 1) * deltaZ);
            uvs[currentUV++] = (horizontalStrip) / xRotations;
            uvs[currentUV++] = (cell + 1.0f) / zRotations;

            vertices[currentVertex++] = cos((cell + 1) * deltaZ);
            vertices[currentVertex++] = sin(horizontalStrip * deltaX) * sin((cell + 1) * deltaZ);
            vertices[currentVertex++] = cos(horizontalStrip * deltaX) * sin((cell + 1) * deltaZ);
            uvs[currentUV++] = (horizontalStrip) / xRotations;

            uvs[currentUV++] = (cell + 1.0f) / zRotations;
            vertices[currentVertex++] = cos(cell * deltaZ);
            vertices[currentVertex++] = sin((horizontalStrip + 1) * deltaX) * sin(cell * deltaZ);
            vertices[currentVertex++] = cos((horizontalStrip + 1) * deltaX) * sin(cell * deltaZ);
            uvs[currentUV++] = (horizontalStrip + 1) / xRotations;

            uvs[currentUV++] = (cell) / zRotations;
            vertices[currentVertex++] = cos((cell + 1) *  deltaZ);
            vertices[currentVertex++] = sin((horizontalStrip + 1) * deltaX) * sin((cell + 1) *  deltaZ);
            vertices[currentVertex++] = cos((horizontalStrip + 1) * deltaX) * sin((cell + 1) *  deltaZ);
            uvs[currentUV++] = (horizontalStrip + 1) / xRotations;
            uvs[currentUV++] = (cell + 1) / zRotations;

        }
        vertices[currentVertex++] = - 1.0f;
        vertices[currentVertex++] = 0.0f;
        vertices[currentVertex++] = 0.0f;
        uvs[currentUV++] = horizontalStrip / zRotations;
        uvs[currentUV++] = 0.0f;
        vertices[currentVertex++] = cos((zRotations - 1) * deltaZ);
        vertices[currentVertex++] = sin(horizontalStrip * deltaX) * sin((zRotations - 1) * deltaZ);
        vertices[currentVertex++] = cos(horizontalStrip * deltaX) * sin((zRotations - 1) * deltaZ);
        uvs[currentUV++] = horizontalStrip / zRotations;
        uvs[currentUV++] = 1.0f / xRotations;
        vertices[currentVertex++] = cos((zRotations - 1) * deltaZ);
        vertices[currentVertex++] = sin((horizontalStrip + 1) * deltaX) * sin((zRotations - 1) * deltaZ);
        vertices[currentVertex++] = cos((horizontalStrip + 1) * deltaX) * sin((zRotations - 1) * deltaZ);
        uvs[currentUV++] = horizontalStrip / zRotations;
        uvs[currentUV++] = 1.0f / xRotations;
        
    
    }
    this->buffers = new std::unordered_map<std::string, BufferObject*>();
    
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->buffers->insert({"vertex", new GLBufferObject<GLfloat>(0, 3, GL_FLOAT, numVertices, vertices)});
    this->buffers->insert({"uvs", new GLBufferObject<GLfloat>(1, 2, GL_FLOAT, numUVs, uvs)});
    this->generateFaceNormals();
    this->generateVertexNormals();
    
    this->bindBuffers();
}

Sphere * Sphere::getInstance() {
    if (!Sphere::Instance) {
        Sphere::Instance = new Sphere();
    }
    return Sphere::Instance;
}

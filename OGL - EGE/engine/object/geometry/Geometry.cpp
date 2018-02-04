//
//  Geometry.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Geometry.hpp"

void Geometry::createVAO(GLuint & id) {
    glGenVertexArrays(1, &id);
}


void Geometry::bindVAO(GLuint & id) {
    glBindVertexArray(id);
}



Geometry::Geometry(GLfloat * vertexBuffer, int vertexBufferSize, GLfloat * uvBuffer) {
    this->buffers = new std::unordered_map<std::string, BufferObject*>();
    this->drawType = GL_TRIANGLES;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
    this->buffers->insert({"vertex", new GLBufferObject<GLfloat>(0, 3, GL_FLOAT, vertexBufferSize, vertexBuffer)});
    this->buffers->insert({"uvs", new GLBufferObject<GLfloat>(1, 2, GL_FLOAT, (vertexBufferSize / 3) * 2, uvBuffer)});
    this->bindBuffers();
}

void Geometry::bindBuffers() {
    this->bindVAO(this->VAOid);
    for( std::unordered_map<std::string, BufferObject*>::const_iterator it = this->buffers->begin(); it != this->buffers->end(); ++it ) {
        it->second->bind();
    }
}

void Geometry::updateUVs(GLfloat * uvs, int size) {
    if (this->buffers->find("uvs") !=  this->buffers->end()) {
        this->bindVAO(this->VAOid);
        this->buffers->at("uvs")->update(uvs, size);
    }
}

void Geometry::updateVertices(GLfloat * vertices, int size) {
    if (this->buffers->find("vertex") !=  this->buffers->end()) {
        this->bindVAO(this->VAOid);
        this->buffers->at("vertex")->update(vertices, size);
    }
}

int Geometry::getVertexBufferSize(std::string key) {
    if (this->buffers->find(key) !=  this->buffers->end()) {
        return this->buffers->at(key)->size / this->buffers->at(key)->dimension;
    }
    else {
        return 0;
    }
}


void Geometry::updateBuffer(std::string key, GLfloat * vertices, int size) {
    if (this->buffers->find(key) !=  this->buffers->end()) {
        this->bindVAO(this->VAOid);
        this->buffers->at(key)->update(vertices, size);
    }
}

void Geometry::generateFaceNormals() {
    GLBufferObject<GLfloat> * vertexBuffer = (GLBufferObject<GLfloat>*)(this->buffers->at("vertex"));
    GLfloat * normalBuffer = new GLfloat[vertexBuffer->size]{ 0.0f };
    for(int i = 0; i < vertexBuffer->size; i += 9) {
        glm::vec3 p1 = glm::vec3(vertexBuffer->data[i], vertexBuffer->data[i + 1], vertexBuffer->data[i + 2]);
        glm::vec3 p2 = glm::vec3(vertexBuffer->data[i + 3], vertexBuffer->data[i + 4], vertexBuffer->data[i + 5]);
        glm::vec3 p3 = glm::vec3(vertexBuffer->data[i + 6], vertexBuffer->data[i + 7], vertexBuffer->data[i + 8]);
        glm::vec3 s1 = p3 - p2;
        glm::vec3 s2 = p1 - p2;
        glm::vec3 normal = glm::cross(s1, s2);
        for (int j = 0; j < 9; j += 3) {
            normalBuffer[i + j] = normal.r;
            normalBuffer[i + j + 1] = normal.g;
            normalBuffer[i + j + 2] = normal.b;
        }
    }
    if (this->buffers->find("facenormals") ==  this->buffers->end()) {
        this->buffers->insert({"facenormals", new GLBufferObject<GLfloat>(2, 3, GL_FLOAT, vertexBuffer->size, normalBuffer)});
        this->buffers->at("facenormals")->bind();
    }
    else {
        this->buffers->at("normals")->update(normalBuffer, vertexBuffer->size);
    }
}

std::string vecToString(glm::vec3 vector) {
    return std::to_string(vector.r) + "&" + std::to_string(vector.g) + "&" + std::to_string(vector.b);
}

glm::vec3 keyToVector(char * key) {
    char ** flts = new char*[3];
    for (int i = 0; i < 3; i++) {
        flts[i] = std::strtok(key, "&");
    }
    return glm::vec3(strtof(flts[0], 0), strtof(flts[1], 0), strtof(flts[2], 0));
}

void Geometry::generateVertexNormals() {
    if (this->drawType == GL_TRIANGLES) {
        GLBufferObject<GLfloat> * vertexBuffer = (GLBufferObject<GLfloat>*)(this->buffers->at("vertex"));
        GLfloat * normalBuffer = new GLfloat[vertexBuffer->size]{ 0.0f };
        std::unordered_map<std::string, glm::vec3> * normals = new std::unordered_map<std::string, glm::vec3>();
        for(int i = 0; i < vertexBuffer->size; i += 9) {
            glm::vec3 p1 = glm::vec3(vertexBuffer->data[i], vertexBuffer->data[i + 1], vertexBuffer->data[i + 2]);
            glm::vec3 p2 = glm::vec3(vertexBuffer->data[i + 3], vertexBuffer->data[i + 4], vertexBuffer->data[i + 5]);
            glm::vec3 p3 = glm::vec3(vertexBuffer->data[i + 6], vertexBuffer->data[i + 7], vertexBuffer->data[i + 8]);
            glm::vec3 s1 = p3 - p2;
            glm::vec3 s2 = p1 - p2;
            glm::vec3 normal = glm::cross(s1, s2);
            if (normals->find(vecToString(p1)) == normals->end()) {
                normals->insert({vecToString(p1), normal});
            }
            else {
                normals->at(vecToString(p1)) = normals->at(vecToString(p1)) + normal;
            }
        
            if (normals->find(vecToString(p2)) == normals->end()) {
                normals->insert({vecToString(p2), normal});
            }
            else {
                normals->at(vecToString(p2)) = normals->at(vecToString(p2)) + normal;
            }
        
            if (normals->find(vecToString(p3)) == normals->end()) {
                normals->insert({vecToString(p3), normal});
            }
            else {
                normals->at(vecToString(p3)) = normals->at(vecToString(p3)) + normal;
            }
        }
        for(int i = 0; i < vertexBuffer->size; i += 3) {
            glm::vec3 vertex = glm::vec3(vertexBuffer->data[i], vertexBuffer->data[i + 1], vertexBuffer->data[i + 2]);
            glm::vec3 n = normals->at(vecToString(vertex));
            normalBuffer[i] = n.r;
            normalBuffer[i + 1] = n.g;
            normalBuffer[i + 2] = n.b;
        }
        if (this->buffers->find("vertexnormals") ==  this->buffers->end()) {
            this->buffers->insert({"vertexnormals", new GLBufferObject<GLfloat>(3, 3, GL_FLOAT, vertexBuffer->size, normalBuffer)});
            this->buffers->at("vertexnormals")->bind();
        }
        else {
            this->buffers->at("vertexnormals")->update(normalBuffer, vertexBuffer->size);
        }
    }
}

void Geometry::generateTangents() {
    GLBufferObject<GLfloat> * vertexBuffer = (GLBufferObject<GLfloat>*)this->buffers->at("vertex");
    GLBufferObject<GLfloat> * uvBuffer = (GLBufferObject<GLfloat>*)this->buffers->at("uvs");
    GLfloat * vertices = vertexBuffer->data;
    GLfloat * uvs = uvBuffer->data;
    int numVerts = vertexBuffer->size;
    
    GLfloat * tangents = new GLfloat[numVerts];
    GLfloat * bitangents = new GLfloat[numVerts];

    int tangentIndex = 0;
    for (int i = 0, j = 0; i < numVerts; i += 9, j += 6){
        glm::vec3 p1(vertices[i], vertices[i + 1], vertices[i + 2]);
        glm::vec3 p2(vertices[i + 3], vertices[i + 4], vertices[i + 5]);
        glm::vec3 p3(vertices[i + 6], vertices[i + 7], vertices[i + 8]);
        
        glm::vec2 uv1(uvs[j], uvs[j + 1]);
        glm::vec2 uv2(uvs[j + 2], uvs[j + 3]);
        glm::vec2 uv3(uvs[j + 4], uvs[j + 5]);
        
        glm::vec3 pDelta1 = p3 - p2;
        glm::vec3 pDelta2 = p1 - p2;
        
        glm::vec2 uvDelta1 = uv3 - uv2;
        glm::vec2 uvDelta2 = uv1 - uv2;
        
        float r = 1.0f / (uvDelta1[0] * uvDelta2[1] - uvDelta1[1] * uvDelta2[0]);
        glm::vec3 tangent = (pDelta1 * uvDelta2[1] - pDelta2 * uvDelta1[1]) * r;
        glm::vec3 bitangent = (pDelta2 * uvDelta1[0] - pDelta1 * uvDelta2[0]) * r;
        for (int l = 0; l < 3; l++){
            for (int k = 0; k < 3; k++){
                tangents[tangentIndex] = tangent[k];
                bitangents[tangentIndex] = bitangent[k];
                tangentIndex++;
            }
        }
    }
    this->buffers->insert({"tangents", new GLBufferObject<GLfloat>(4, 3, GL_FLOAT, numVerts, tangents)});
    this->buffers->insert({"bitangents", new GLBufferObject<GLfloat>(5, 3, GL_FLOAT, numVerts, bitangents)});
}


Geometry::Geometry() {
    this->buffers = new std::unordered_map<std::string, BufferObject*>();
    this->drawType = GL_POINTS;
    this->createVAO(this->VAOid);
    this->bindVAO(this->VAOid);
}

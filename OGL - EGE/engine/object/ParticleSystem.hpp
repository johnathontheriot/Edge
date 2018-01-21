//
//  ParticleSystem.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/20/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>
#include "GLObject.hpp"

class ParticleSystem : public GLObject {
private:
    int numParticles;
    GLfloat pointSize;
public:
    ParticleSystem(int numParticles, GLfloat pointSize = 10.0f) {
        this->numParticles = numParticles;
        this->geometry = new Geometry();
        this->pointSize = pointSize;
    }
    
    void addDimension(std::string name, GLfloat * particleData, int bufferSize) {
        this->geometry->buffers->insert({name, new GLBufferObject<GLfloat>(this->geometry->bufferListSize++, bufferSize / this->numParticles, GL_FLOAT, bufferSize, particleData)});
    }
    
    void bindBuffers() {
        this->geometry->bindBuffers();
    }
    
    void render(Scene* scene, ShaderProgram* program = NULL) {
        glEnable(GL_BLEND);
        glDisable(GL_CULL_FACE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPointSize(this->pointSize);
        GLObject::render(scene, program);
        glEnable(GL_CULL_FACE);
        glDisable(GL_BLEND);
    }
    
    void setGeometry(Geometry * geometry) {
        this->geometry = geometry;
    }
    
    void addDivisingDimension(std::string name, GLfloat * particleData, int bufferSize) {
        this->geometry->buffers->insert({name, new DivisingBufferObject<GLfloat>(1, this->geometry->bufferListSize++, bufferSize / this->numParticles, GL_FLOAT, bufferSize, particleData)});
    }
    
protected:
};

#endif /* ParticleSystem_hpp */

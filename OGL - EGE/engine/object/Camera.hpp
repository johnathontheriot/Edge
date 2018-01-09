//
//  Camera.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <glm/mat4x4.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera {
private:
    float azumith;
    float elevation;
    GLfloat fov;
    GLfloat aspect;
    GLfloat near;
    GLfloat far;
public:
    friend class Scene;
    glm::mat4x4 viewMatrix;
    glm::mat4x4 localScale;
    glm::mat4x4 localTranslation;
    glm::mat4x4 localRotation;
    glm::mat4x4 globalScale;
    glm::mat4x4 globalTranslation;
    glm::mat4x4 globalAzumith;
    glm::mat4x4 globalElevation;
    void changeFOV(float delta);
    Camera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);
    void moveCamera(float azumith, float elevation);
    void alterAzumith(float azumith);
    void alterElevation(float elevation);
    void zoom(float delta);
    void translateLocal(GLfloat x, GLfloat y, GLfloat z);
    void scaleLocal(GLfloat x, GLfloat y, GLfloat z);
    void rotateLocal(GLfloat x, GLfloat y, GLfloat z);
    void translateGlobal(GLfloat x, GLfloat y, GLfloat z);
    void scaleGlobal(GLfloat x, GLfloat y, GLfloat z);
    glm::mat4x4 getViewMatrix();
    glm::mat4x4 getProjectionMatrix();
};

#endif /* Camera_hpp */

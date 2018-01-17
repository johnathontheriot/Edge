//
//  Camera.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/6/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "Camera.hpp"
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Script.hpp"

Camera::Camera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far, GLfloat left, GLfloat right, GLfloat top, GLfloat bottom) {
    this->localScale = glm::mat4x4(1.0f);
    this->localTranslation = glm::mat4x4(1.0f);
    this->localRotation = glm::mat4x4(1.0f);
    this->globalScale = glm::mat4x4(1.0f);
    this->globalTranslation = glm::mat4x4(1.0f);
    this->globalAzumith = glm::mat4x4(1.0f);
    this->globalElevation = glm::mat4x4(1.0f);
    this->viewMatrix = glm::mat4x4(1.0f);
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
}

void Camera::changeFOV(float delta) {
    if ((delta < 0 && this->fov > 0) || (delta > 0 && this->fov < 360)) {
        this->fov += delta;
    }
}

void Camera::makeOrthographic() {
    this->projection = ProjectionType::ORTHOGRAPHIC;
}

void Camera::makePerspective() {
    this->projection = ProjectionType::PERSPECTIVE;
}

glm::mat4x4 Camera::getProjectionMatrix() {
    float l = this->orthographicVal * this->left;
    float r = this->orthographicVal * this->right;
    float t = this->orthographicVal * this->top;
    float b = this->orthographicVal * this->bottom;
    float n = this->orthographicVal * this->near;
    float f = this->orthographicVal * this->far;
    switch (this->projection) {
        case ProjectionType::ORTHOGRAPHIC:
            return glm::transpose(glm::mat4x4(2.0f / (r - l), 0, 0, -(r + l) / (r - l),
                               0, 2.0f / (t - b), 0, -(t + b) / (t - b),
                               0, 0, - 2.0f / (f - n), -(f + n) / (f - n),
                               0, 0, 0, 1.0f));
        case ProjectionType::PERSPECTIVE:
        default:
            GLfloat s = 1.0f / (tan((fov / 2.0f) * (M_PI / 180.0f)));
            return glm::mat4x4(s / (aspect), 0, 0, 0,
                       0, s, 0, 0,
                       0, 0, -(far + near) / (far - near), -1.0f,
                       0, 0, -(2.0f * far * near) / (far - near), 0);
    }
}

void Camera::moveCamera(float azumith, float elevation) {
    this->alterAzumith(azumith);
    this->alterElevation(elevation);
}


void Camera::alterAzumith(float azumith) {
    this->azumith += azumith;
    glm::mat4x4 azumithTransform = glm::mat4x4(std::cos(this->azumith), 0, - std::sin(this->azumith), 0,
                                               0, 1.0f, 0, 0,
                                               std::sin(this->azumith), 0, std::cos(this->azumith), 0,
                                               0, 0, 0, 1.0f);
    this->globalAzumith = azumithTransform;
    
}

void Camera::alterElevation(float elevation) {
    this->elevation += elevation;
    glm::mat4x4 elevationTransform = glm::mat4x4(1.0f,  0, 0, 0,
                                                 0, std::cos(this->elevation), std::sin(this->elevation), 0,
                                                 0, - std::sin(this->elevation), std::cos(this->elevation), 0,
                                                 0, 0, 0, 1.0f);
    this->globalElevation = elevationTransform;
    
}

glm::mat4x4 Camera::getViewMatrix() {
    return this->globalTranslation * this->globalElevation * this->globalAzumith * this->globalScale * this->localTranslation * this->localRotation * this->localScale  * this->viewMatrix;
}

glm::mat4x4 Camera::getScaleRotationMatrix() {
    return  this->globalElevation * this->globalAzumith * this->globalScale  * this->localRotation * this->localScale  * this->viewMatrix;
}

void Camera::zoom(float delta){
    this->orthographicVal -= delta;
    this->globalTranslation = this->globalTranslation * glm::mat4x4(1.0f, 0, 0, 0,
                                                                            0, 1.0f, 0, 0,
                                                                            0, 0, 1.0f, 0,
                                                                            0, 0, delta, 1);
}

void Camera::translateLocal(GLfloat x, GLfloat y, GLfloat z) {
    this->localTranslation = this->localTranslation * glm::mat4x4(1, 0, 0, 0,
                                                                  0, 1, 0, 0,
                                                                  0, 0, 1, 0,
                                                                  x, y, z, 1);
}

void Camera::scaleLocal(GLfloat x, GLfloat y, GLfloat z) {
    this->localScale = this->localScale * glm::mat4x4(x, 0, 0, 0,
                                                      0, y, 0, 0,
                                                      0, 0, z, 0,
                                                      0, 0, 0, 1);
}

void Camera::rotateLocal(GLfloat x, GLfloat y, GLfloat z){
    glm::mat4x4 rotation = glm::mat4x4(1.0f);
    rotation = x == 0 ? rotation : rotation * glm::mat4x4(1,  0, 0, 0,
                                                          0, std::cos(x), std::sin(x), 0,
                                                          0, - std::sin(x), std::cos(x), 0,
                                                          0, 0, 0, 1);
    rotation = y == 0 ? rotation : rotation * glm::mat4x4(std::cos(y), 0, - std::sin(y), 0,
                                                          0, 1, 0, 0,
                                                          std::sin(y), 0, std::cos(y), 0,
                                                          0, 0, 0, 1);
    rotation = z == 0 ? rotation : rotation * glm::mat4x4(std::cos(z), std::sin(z), 0, 0,
                                                          - std::sin(z), std::cos(z), 0, 0,
                                                          0, 0, 1, 0,
                                                          0, 0, 0, 1);
    this->localRotation = this->localRotation * rotation;
}

void Camera::translateGlobal(GLfloat x, GLfloat y, GLfloat z) {
    this->globalTranslation = this->globalTranslation * glm::mat4x4(1, 0, 0, 0,
                                                                    0, 1, 0, 0,
                                                                    0, 0, 1, 0,
                                                                    x, y, z, 1);
}

void Camera::scaleGlobal(GLfloat x, GLfloat y, GLfloat z) {
    this->globalScale = this->globalScale * glm::mat4x4(x, 0, 0, 0,
                                                        0, y, 0, 0,
                                                        0, 0, z, 0,
                                                        0, 0, 0, 1);
}


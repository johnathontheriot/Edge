//
//  PostProcessor.cpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/18/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#include "PostProcessor.hpp"

template<> void PostProcessor::addBuffer<TextureBuffer>(std::string name, StorageBuffer * buffer) {
    buffer->bindToFrame(this->colorAttachment++);
    this->buffers->insert({name, buffer});
}

template<> void PostProcessor::addBuffer<HDRTextureBuffer>(std::string name, StorageBuffer * buffer) {
    buffer->bindToFrame(this->colorAttachment++);
    this->buffers->insert({name, buffer});
}

template<> void PostProcessor::addBuffer<DepthBuffer>(std::string name, StorageBuffer * buffer) {
    buffer->bindToFrame(GL_DEPTH_ATTACHMENT);
    this->buffers->insert({name, buffer});
}

template<> void PostProcessor::addBuffer<LowResTextureBuffer>(std::string name, StorageBuffer * buffer) {
    buffer->bindToFrame(this->colorAttachment++);
    this->buffers->insert({name, buffer});
}

template<> void PostProcessor::addBuffer<DepthTextureBuffer>(std::string name, StorageBuffer * buffer) {
    buffer->bindToFrame(GL_DEPTH_ATTACHMENT);
    this->buffers->insert({name, buffer});
}

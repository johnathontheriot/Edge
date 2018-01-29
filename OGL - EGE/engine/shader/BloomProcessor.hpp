//
//  BloomProcessor.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/21/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef BloomProcessor_hpp
#define BloomProcessor_hpp

#include <stdio.h>
#include "PostProcessor.hpp"
#include "RectangularPlane.hpp"
#include <list>
#include "SceneManager.hpp"
#include "Utilities.hpp"
#include "HDRProcessor.hpp"
#include "LuminanceProcessor.hpp"
#include "PostProcessorPipeline.hpp"
#include "GaussianProcessor.hpp"

class BloomBlenderProcessor: public PostProcessor {
    std::unordered_map<std::string, IGLObject*> * objects;
public:
    BloomBlenderProcessor(ShaderProgram * shader, Dimensions * d) : PostProcessor(shader, d) {
        this->objects = new std::unordered_map<std::string, IGLObject*>();
        this->objects->insert({"plane", new GLObject(RectangularPlane::getInstance())});
        //this->frame->bind();
        //this->addBuffer<HDRTextureBuffer>("texBuffer", new HDRTextureBuffer( d->width,  d->height));
        //this->addBuffer<DepthBuffer>("depthBuffer", new DepthBuffer(d->width, d->height));
        //this->draw();
        //this->frame->unbind();
        this->frame->id = 0;
    }
    
    std::unordered_map<std::string, StorageBuffer*> * render(Scene * scene, Dimensions * viewPort, std::unordered_map<std::string, IGLObject*> * objects) {
        return  PostProcessor::render(scene, viewPort, this->objects);
    }
};

class BloomProcessor : public PostPorcessorPipeline {
public:
    BloomProcessor(Dimensions * d) {
        this->processors = new std::list<PostProcessor*>();
        std::list<PostProcessor*>::iterator it = this->processors->begin();
        // HIGH RES RENDER OF SCENE
        HighResProcessor * highRes = new HighResProcessor(NULL, d);
        this->processors->push_back(highRes);
        ShaderProgram * lumShader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/luminance.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/luminance.fragment.glsl");
        lumShader->bindVars = [highRes](ShaderProgram * shader, GLObject* obj, Scene* scene) {
            shader->bindVariable<Texture>("tex", highRes->buffers->at("texBuffer"));
        };
        // RENDER LUMINANCE
        LuminanceProcessor * lum = new LuminanceProcessor(lumShader, d);
        this->processors->push_back(lum);
        float * weights = Utilities::gaussianWeights(1, 5);
        // BLUR LUMINANCE
        ShaderProgram * gaussShader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/gaussian_blur.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/gaussian_blur.fragment.glsl");
        gaussShader->bindVars = [lum, weights](ShaderProgram * shader, GLObject* obj, Scene* scene) {
            shader->bindVariable<Texture>("tex", lum->buffers->at("texBuffer"));
            shader->bindVariable("weights", weights, 5);
        };
        gaussShader->addFragmentSubroutineCall("blurPass1");
        
        GaussianProcessor * gauss = new GaussianProcessor(gaussShader, d);
        this->processors->push_back(gauss);
        
        ShaderProgram * gaussShaderSecond = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/gaussian_blur.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/gaussian_blur.fragment.glsl");
        gaussShaderSecond->bindVars = [weights, gauss](ShaderProgram * shader, GLObject* obj, Scene* scene) {
            shader->bindVariable<Texture>("tex", gauss->buffers->at("texBuffer"));
            shader->bindVariable("weights", weights, 5);
        };
        gaussShaderSecond->addFragmentSubroutineCall("blurPass2");

        GaussianProcessor * gaussSecond = new GaussianProcessor(gaussShaderSecond, d);
        this->processors->push_back(gaussSecond);
        // APPLY BLOOM
        ShaderProgram * bloomShader = ShaderManager::createShaderProgram("/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/bloom_blend.vertex.glsl", "/Users/johnathontheriot/Desktop/OGL - EGE/OGL - EGE/bloom_blend.fragment.glsl");
        bloomShader->bindVars = [gaussSecond, highRes](ShaderProgram * shader, GLObject* obj, Scene* scene) {
            shader->bindVariable<Texture>("scene", highRes->buffers->at("texBuffer"));
            shader->bindVariable<Texture>("blur", gaussSecond->buffers->at("texBuffer"));
        };
        BloomBlenderProcessor * bloomBlender = new BloomBlenderProcessor(bloomShader, d);
        this->processors->push_back(bloomBlender);
    }
};
#endif /* BloomProcessor_hpp */

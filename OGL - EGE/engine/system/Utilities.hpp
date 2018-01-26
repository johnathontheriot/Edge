//
//  Utilities.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/13/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef Utilities_hpp
#define Utilities_hpp

#include <stdio.h>
#include <glm/vec4.hpp>
#include <cmath>

class Utilities {
private:
public:
    static glm::vec4 toColor(int hex) {
        int sig = 0x000000FF;
        int r = (hex >> 24) & sig;
        int g = (hex >> 16) & sig;
        int b = (hex >> 8) & sig;
        int a = hex & sig;
        return glm::vec4((r * 1.0f) / 255.0f, (g * 1.0f) / 255.0f, (b * 1.0f) / 255.0f, (a * 1.0f) / 255.0f);
    }
    
    static float gaussianDistribution(float x, float sigma, float p = 0) {
        return (1 / (sigma * sqrtf(2.0 * M_PI))) * pow(M_E, (-(1.0 / 2.0) * pow((x - p) / (sigma), 2)));
    }
    
    static float * gaussianWeights(float sigma, int size, float p = 0, float inc = 1) {
        if (size < 1) {
            return NULL;
        }
        float * weights = new float[size];
        float sum = 0.0;
        weights[0] = Utilities::gaussianDistribution(0, sigma, p);
        for (int i = 1; i < size; i++) {
            weights[i] = Utilities::gaussianDistribution(inc * i, sigma, p);
            sum += (weights[i] * 2.0);
        }
        for (int i = 0; i < size; i++) {
            weights[i] = 1 - (weights[i] / sum);
        }
        return weights;
    }
protected:
};

#endif /* Utilities_hpp */

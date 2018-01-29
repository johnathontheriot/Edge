//
//  PostProcessorPipeline.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/28/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef PostProcessorPipeline_hpp
#define PostProcessorPipeline_hpp

#include <stdio.h>
#include "PostProcessor.hpp"

class PostPorcessorPipeline {
public:
    
    std::list<PostProcessor*> * processors;
    
    PostProcessor* getLast() {
        return this->processors->back();
    }
    
};

#endif /* PostProcessorPipeline_hpp */

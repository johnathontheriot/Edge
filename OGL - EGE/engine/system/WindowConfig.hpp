//
//  WindowConfig.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/5/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef WindowConfig_hpp
#define WindowConfig_hpp

#include "../../vendor/json.hpp"

using json = nlohmann::json;


class WindowConfig {
public:
    int width;
    int height;
    std::string title;
    std::string name;
    bool fullScreen;
    WindowConfig(json config);
};

#endif /* WindowConfig_hpp */

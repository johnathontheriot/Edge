//
//  TextureManager.hpp
//  OGL - EGE
//
//  Created by Johnathon Theriot on 1/7/18.
//  Copyright © 2018 Johnathon Theriot. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <unordered_map>
#include "Texture.hpp"

class TextureManager {
private:
    TextureManager();
public:
    std::unordered_map<std::string, Texture *> * textures;
    static TextureManager * Instance;
    static TextureManager * getInstance();
    static ImageData loadBMP(const char * path);
    Texture * loadTexture(std::string, std::string);
    Texture * loadTexture(std::string, ImageData);
protected:
};

#endif /* TextureManager_hpp */

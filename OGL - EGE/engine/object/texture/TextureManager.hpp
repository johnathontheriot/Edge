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
#include "BMPTexture.hpp"
#include "DDSTexture.hpp"
#include "CubeMap.hpp"

class BMPTexture;
class DDSTexture;
class Texture;

class TextureManager {
private:
    TextureManager();
public:
    static int textureNumber;
    static int textureEnum;
    std::unordered_map<std::string, Texture *> * textures;
    static TextureManager * Instance;
    static TextureManager * getInstance();
    Texture * loadCubeMap(std::string, std::string, std::string, std::string, std::string, std::string, std::string);
    template<typename T, typename std::enable_if<std::is_base_of<Texture, T>::value>::type* = nullptr>
    T * loadImage(const char * path);
    template<typename T, typename std::enable_if<std::is_base_of<Texture, T>::value>::type* = nullptr>
    T * loadTexture(std::string name, std::string path) {
        T * texture = TextureManager::loadImage<T>(path.c_str());
        texture->bind(TextureManager::textureEnum++, TextureManager::textureNumber++);
        this->textures->insert({name, texture});
        return texture;
    }
    Texture * loadTexture(std::string, std::string);

protected:
};

#endif /* TextureManager_hpp */

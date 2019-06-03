#ifndef SDL_TEXTUREFACTORY_H
#define SDL_TEXTUREFACTORY_H

#include <map>
#include <string>
#include <SDL2/SDL_system.h>
#include "Renderer.h"

class TextureFactory {
public:
    TextureFactory();
    ~TextureFactory();
    void init(Renderer& renderer);
    SDL_Texture* getTextureByName(std::string &name);

private:
    std::map<std::string, SDL_Texture*> textures;
    SDL_Texture* loadTexture(const std::string& filename, Renderer& renderer);

};


#endif //SDL_TEXTUREFACTORY_H

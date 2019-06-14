//
// Created by jonathanmedina on 02/06/19.
//

#include <SDL2/SDL_image.h>
#include "TextureFactory.h"
#include "ComponentsSDL/SDLException.h"

TextureFactory::TextureFactory() : textures(textures) {
    IMG_Init(IMG_INIT_PNG);
}

TextureFactory::~TextureFactory() {
    for (auto& elem : textures) {
        SDL_DestroyTexture(elem.second);
    }
}

void TextureFactory::init(Renderer& renderer) {
    textures["chell"] = loadTexture(std::string("assets/textures/chell.png"), renderer);
    textures["block"] = loadTexture(std::string("assets/textures/block.png"), renderer);
    textures["gate"] = loadTexture(std::string("assets/textures/gates.png"), renderer);
    textures["bulletAndRock"] = loadTexture(std::string("assets/textures/bulletAndRock.png"), renderer);
    textures["acidAndButtons"] = loadTexture(std::string("assets/textures/acidAndButtons.png"), renderer);
    textures["background"] = loadTexture(std::string("assets/backgroundImage/background.png"), renderer);
}

SDL_Texture *TextureFactory::getTextureByName(std::string &name) {
    return textures[name];
}

SDL_Texture *TextureFactory::loadTexture(const std::string &filename, Renderer& renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer.getRenderer(), filename.c_str());
    if (!texture) {
        throw SDLException("Error while loading texture", SDL_GetError());
    }
    return texture;
}

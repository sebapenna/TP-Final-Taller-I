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
    textures["cake"] = loadTexture(std::string("assets/textures/cake.png"), renderer);
    textures["portal"] = loadTexture(std::string("assets/textures/portal.png"), renderer);
    textures["pintool"] = loadTexture(std::string("assets/textures/pintool.png"), renderer);
    //setColor(textures["chell"], 255, 0, 0);
}


SDL_Texture *TextureFactory::getBlockTexture() {
    return textures["block"];
}

SDL_Texture *TextureFactory::getGateTexture() {
    return textures["gate"];
}

SDL_Texture *TextureFactory::getCakeTexture() {
    return textures["cake"];
}

SDL_Texture *TextureFactory::getPortalTexture() {
    return textures["portal"];
}

SDL_Texture *TextureFactory::getPintoolTexture() {
    return textures["pintool"];
}

SDL_Texture *TextureFactory::getBulletAndRocksTexture() {
    return textures["bulletAndRock"];
}

SDL_Texture *TextureFactory::getBackground() {
    return textures["background"];
}

SDL_Texture *TextureFactory::getAcidAndButtonsTexture() {
    return textures["acidAndButtons"];
}

SDL_Texture *TextureFactory::getChellTexture() {
    return textures["chell"];
}

SDL_Texture *TextureFactory::loadTexture(const std::string &filename, Renderer& renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer.getRenderer(), filename.c_str());
    if (!texture) {
        throw SDLException("Error while loading texture", SDL_GetError());
    }
    return texture;
}

void TextureFactory::setColor(SDL_Texture* texture, int r, int g, int b) {
    int error = SDL_SetTextureColorMod(texture, r, g, b);
    if (error) {
        throw SDLException("Error while changing color in chell texture", SDL_GetError());
    }
}

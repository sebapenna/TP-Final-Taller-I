#ifndef SDL_TEXTUREFACTORY_H
#define SDL_TEXTUREFACTORY_H

#include <map>
#include <string>
#include <SDL2/SDL_system.h>
#include "Renderer.h"
// Holds all the textures needed in the game
class TextureFactory {
private:
    std::map<std::string, SDL_Texture*> textures;
    // Loads a texture from a file
    SDL_Texture* loadTexture(const std::string& filename, Renderer& renderer);
    void setColor(SDL_Texture* texture, int r, int g, int b);
public:
    TextureFactory();
    ~TextureFactory();
    // Initializes the factory
    void init(Renderer& renderer);

    SDL_Texture* getBlockTexture();
    SDL_Texture* getGateTexture();
    SDL_Texture* getCakeTexture();
    SDL_Texture* getPortalTexture();
    SDL_Texture* getPintoolTexture();
    SDL_Texture* getBulletAndRocksTexture();
    SDL_Texture* getBackground();
    SDL_Texture* getAcidAndButtonsTexture();

    SDL_Texture* getDyingChellTexture();
    SDL_Texture* getFiringChellTexture();
    SDL_Texture* getFlyingChellTexture();
    SDL_Texture* getRestingIdleChellTexture();
    SDL_Texture* getRunningChellTexture();
    SDL_Texture* getWinningChellTexture();
};


#endif //SDL_TEXTUREFACTORY_H

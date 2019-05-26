#include "Renderer.h"
#include "SDLException.h"

Renderer::Renderer(Window& window) :
        window(window),
        renderer(SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)), // | SDL_RENDERER_PRESENTVSYNC
        windowWidth(window.getWidth()), windowHeight(window.getHeight()) {
    if (!renderer)
        throw SDLException("Create renderer error: %s", SDL_GetError());
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

void Renderer::copyTexture(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst) {
    SDL_RenderCopy(renderer, texture, src, dst);
}

void Renderer::copyTexture(SDL_Texture* texture, SDL_Rect *dst) {
    SDL_RenderCopy(renderer, texture, NULL, dst);
}

void Renderer::clearRender() {
    SDL_RenderClear(renderer);
}

void Renderer::render() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Renderer::getRenderer() {
    return renderer;
}

void Renderer::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

int Renderer::getWindowWidth() {
    return window.getWidth();
}

int Renderer::getWindowHeight() {
    return window.getHeight();
}

Uint32 Renderer::getWindowID() {
    return window.getID();
}

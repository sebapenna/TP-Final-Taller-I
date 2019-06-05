#include "Window.h"
#include "SDLException.h"

Window::Window(const std::string &title, int width, int height, Uint32 flag) :
        width(width), height(height) {
    int errCode = SDL_Init(SDL_INIT_VIDEO);
    if (errCode) {
        throw SDLException("Error while trying to initialize", SDL_GetError());
    }
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              flag);
    if (!window) throw SDLException("Error while trying to initialize", SDL_GetError());
}

Window::~Window() {
    SDL_DestroyWindow(window);
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

SDL_Window* Window::getWindow() {
    return window;
}

void Window::showErrorMessage(const std::string& title, const std::string& description) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), description.c_str(), window);
}

Uint32 Window::getID() {
    return SDL_GetWindowID(window);
}
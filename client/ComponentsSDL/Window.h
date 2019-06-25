#ifndef TOWERDEFENSE_WINDOW_H
#define TOWERDEFENSE_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <string>

// This is an abstraction for the SDL_Window
// Allows to do the basic method of it
class Window {
private:
    SDL_Window* window;
    int width;
    int height;

public:
    Window(const std::string& title, int width, int height, Uint32 flag);
    ~Window();
    int getWidth();
    int getHeight();
    SDL_Window* getWindow();
    void showErrorMessage(const std::string &title, const std::string
        &description);
    Uint32 getID();
};

#endif

#ifndef __SDL_EXCEPTION_H__
#define __SDL_EXCEPTION_H__
#include <string>
#include <exception>

class SDLException : public std::exception {
public:
    SDLException(const char* description, const char* sdlError);
    const char* what() const noexcept;
private:
    std::string description;
};

#endif

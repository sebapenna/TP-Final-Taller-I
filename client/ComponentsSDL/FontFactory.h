//
// Created by jonathanmedina on 22/06/19.
//

#ifndef PORTAL_FONTFACTORY_H
#define PORTAL_FONTFACTORY_H


#include <string>
#include <map>
#include <SDL2/SDL_ttf.h>

class FontFactory {
private:
    std::map<std::string, TTF_Font *> fonts;
    TTF_Font* loadFontFromFile(std::string file_name, int len);
public:
    FontFactory();
    ~FontFactory();
    TTF_Font* getFont(std::string& file_name);

};


#endif //PORTAL_FONTFACTORY_H

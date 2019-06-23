//
// Created by jonathanmedina on 22/06/19.
//

#include "FontFactory.h"
#include "SDLException.h"


FontFactory::FontFactory() {
    if (TTF_Init() == -1 ) {
        throw SDLException("Error while initializating fonts", TTF_GetError());
    }
    fonts["regular_font"] = loadFontFromFile("assets/fonts/Roboto-Regular.ttf", 20);
}

FontFactory::~FontFactory() {
    for (auto& font : fonts) {
        TTF_CloseFont(font.second);
    }
    TTF_Quit();
}

TTF_Font *FontFactory::getFont(std::string &file_name) {
    return fonts[file_name];
}

TTF_Font* FontFactory::loadFontFromFile(std::string file_name, int len) {
    TTF_Font* font = TTF_OpenFont(file_name.c_str(), 28 );
    if (!font) {
        throw SDLException("Error while loading fonts", TTF_GetError());
    }
    return font;
}

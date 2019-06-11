//
// Created by jonathanmedina on 11/06/19.
//

#ifndef PORTAL_BACKGROUNDVIEW_H
#define PORTAL_BACKGROUNDVIEW_H


#include <client/ComponentsSDL/Sprite.h>
#include "View.h"

class BackgroundView : public View {
private:
    Sprite background;
public:
    BackgroundView(SDL_Texture* texture, Renderer& renderer, int x = 0, int y = 0);
    void draw(Camera& camera);

};


#endif //PORTAL_BACKGROUNDVIEW_H

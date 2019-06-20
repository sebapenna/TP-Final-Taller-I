//
// Created by jonathanmedina on 20/06/19.
//

#ifndef PORTAL_PINTOOLVIEW_H
#define PORTAL_PINTOOLVIEW_H


#include <client/ComponentsSDL/Sprite.h>
#include "View.h"

class PinToolView : public View {
private:
    int id;
    Sprite pintool;
    int16_t tilted;
public:
    PinToolView(int id, SDL_Texture* texture, Renderer& renderer, int16_t tilted, int x = 0, int y = 0);
    void draw(Camera& camera);

    int getId() const;
};


#endif //PORTAL_PINTOOLVIEW_H

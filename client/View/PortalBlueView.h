//
// Created by jonathanmedina on 20/06/19.
//

#ifndef PORTAL_PORTALBLUEVIEW_H
#define PORTAL_PORTALBLUEVIEW_H

#include <client/ComponentsSDL/AnimatedSprite.h>
#include "View.h"
enum PortalColor {BLUE, ORANGE};
class PortalBlueView : public View {
private:
    AnimatedSprite portal;
    int16_t tilted;
public:
    PortalBlueView(SDL_Texture* texture, Renderer& renderer, int16_t tilted, int x = 0, int y = 0);
    void draw(Camera& camera);

};


#endif //PORTAL_PORTALBLUEVIEW_H

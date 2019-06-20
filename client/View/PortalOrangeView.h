//
// Created by jonathanmedina on 20/06/19.
//

#ifndef PORTAL_PORTALORANGEVIEW_H
#define PORTAL_PORTALORANGEVIEW_H


#include <client/ComponentsSDL/AnimatedSprite.h>
#include "View.h"

class PortalOrangeView : public View {
private:
    int id;
    AnimatedSprite portal;
    int16_t tilted;
public:
    PortalOrangeView(int id, SDL_Texture* texture, Renderer& renderer, int16_t tilted, int x = 0, int y = 0);
    void draw(Camera& camera);

    int getId() const;
};


#endif //PORTAL_PORTALORANGEVIEW_H

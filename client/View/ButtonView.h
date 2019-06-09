//
// Created by jonathanmedina on 09/06/19.
//

#ifndef PORTAL_BUTTONVIEW_H
#define PORTAL_BUTTONVIEW_H


#include <client/ComponentsSDL/Sprite.h>
#include "View.h"
enum ButtonState{activated, deactivated};
class ButtonView : public View {
private:
    int id;
    Sprite deactivatedButton;
    Sprite activatedButton;
    ButtonState state;
public:
    ButtonView(int id, SDL_Texture* texture, Renderer& renderer, int  x = 0, int y = 0);
    int getId() const;
    void draw(Camera& camera);
    void enable();
    void disable();
};


#endif //PORTAL_BUTTONVIEW_H

//
// Created by jonathanmedina on 09/06/19.
//

#include "ButtonView.h"


ButtonView::ButtonView(int id, SDL_Texture *texture, Renderer &renderer, int x, int y) :
        View(x, y), id(id),
        deactivatedButton(texture, renderer),
        activatedButton(texture, renderer), state(ButtonState::deactivated) {
    deactivatedButton.setSourceRect(1, 116, 175, 55);
    activatedButton.setSourceRect(1, 192, 175, 74);

}

void ButtonView::draw(Camera &camera) {
    if (this->state == ButtonState::activated) {
        activatedButton.draw(camera,this->getDst());
    } else if (this->state == ButtonState::deactivated) {
        deactivatedButton.draw(camera,this->getDst());
    }
}

void ButtonView::enable() {
    this->state = ButtonState::activated;
}

void ButtonView::disable() {
    this->state = ButtonState::deactivated;
}

int ButtonView::getId() const {
    return id;
}


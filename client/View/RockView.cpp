//
// Created by jonathanmedina on 08/06/19.
//

#include "RockView.h"
#include <stdlib.h>
#include <time.h>

RockView::RockView(int id, SDL_Texture *texture, Renderer &renderer, int x, int y) :
            View(x, y), id(id),
            rock(texture, renderer) {
    int random = rand() % 3;
    if (random == 0) {
        rock.setSourceRect(93, 4528, 72, 54);
    } else if (random == 1) {
        rock.setSourceRect(182, 4523, 67, 60);
    } else if (random == 2) {
        rock.setSourceRect(268, 4515, 66, 73);
    }
}

void RockView::draw(Camera &camera) {
    rock.draw(camera,this->getDst());
}

int RockView::getId() const {
    return id;
}

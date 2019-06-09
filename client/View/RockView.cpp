//
// Created by jonathanmedina on 08/06/19.
//

#include "RockView.h"
#include <stdlib.h>
#include <time.h>

RockView::RockView(SDL_Texture *texture, Renderer &renderer, int x, int y) : View(x, y), rock(texture, renderer) {
    srand (time(NULL));
    int random = rand() % 3;
    if (random == 0) {
        rock.setSourceRect(87, 4513, 85, 83);
    } else if (random == 1) {
        rock.setSourceRect(173, 4513, 85, 83);
    } else if (random == 2){
        rock.setSourceRect(259, 4513, 85, 83);
    }
}

void RockView::draw(Camera &camera) {
    rock.draw(camera,this->getDst());
}

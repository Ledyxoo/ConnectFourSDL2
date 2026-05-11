#pragma once

#include "Settings.h"

typedef struct Assets_s
{
    SDL_Texture *textureExample;
    SDL_Texture* redtoken;
    SDL_Texture* yellowtoken;
    SDL_Texture* lose;
	SDL_Texture* win;
    SDL_Texture* tied;

} Assets;

Assets *Assets_New(SDL_Renderer *renderer);
void Assets_Delete(Assets *self);

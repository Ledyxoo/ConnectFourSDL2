#include "Input.h"
#include <math.h>
#include "Common.h"
#include "Settings.h"
#include "Game.h"
#include "AI.h"

Input *Input_New()
{
    Input *self = (Input *)calloc(1, sizeof(Input));
    AssertNew(self);

    return self;
}

void Input_Delete(Input *self)
{
    if (!self) return;
    free(self);
}

void Input_Update(Input *self)
{
    self->quitPressed = false;
    self->a = false;
    self->z = false;
    self->e = false;
    self->r = false;
    self->t = false;
    self->y = false;
    self->u = false;
    self->ty = false;
    self->tr = false;

    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {

        switch (evt.type)
        {
        case SDL_QUIT:
            self->quitPressed = true;
            break;
        

        case SDL_KEYDOWN:
            if (evt.key.repeat)
                break;

            switch (evt.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                self->quitPressed = true;
                break;
            case SDL_SCANCODE_0:
            case SDL_SCANCODE_KP_0:
                self->a = true;
                break;
            case SDL_SCANCODE_1:
            case SDL_SCANCODE_KP_1:
                self->z = true;
                break;
            case SDL_SCANCODE_2:
            case SDL_SCANCODE_KP_2:
                self->e = true;
                break;
            case SDL_SCANCODE_3:
            case SDL_SCANCODE_KP_3:
                self->r = true;
                break;
            case SDL_SCANCODE_4:
            case SDL_SCANCODE_KP_4:
                self->t = true;
                break;
            case SDL_SCANCODE_5:
            case SDL_SCANCODE_KP_5:
                self->y = true;
                break;
            case SDL_SCANCODE_6:
            case SDL_SCANCODE_KP_6:
                self->u = true;
                break;
            

            default:
                break;
            }
            break;

        case SDL_KEYUP:
            if (evt.key.repeat)
                break;

            switch (evt.key.keysym.scancode)
            {
            default:
                break;
            }
            break;
        }
    }
}

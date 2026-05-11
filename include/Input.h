#pragma once

#include "Settings.h"

typedef struct Input_s
{
    bool quitPressed;
    bool a;
    bool z;
    bool e;
    bool r;
    bool t;
    bool y;
    bool u;
    bool ty;
	bool tr;


} Input;

Input *Input_New();
void Input_Delete(Input *self);
void Input_Update(Input *self);

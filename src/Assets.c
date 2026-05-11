#include "Assets.h"

typedef struct TextureSpec_s
{
    SDL_Texture **ptr;
    char *path;
} TextureSpec;

Assets *Assets_New(SDL_Renderer *renderer)
{
    Assets *self = (Assets *)calloc(1, sizeof(Assets));
    AssertNew(self);

    // -------------------------------------------------------------------------
    // Chargement des textures

    TextureSpec texSpecs[] = {
        { &self->textureExample, "Assets/grilleM.png" },
    };
    //Affiche redtoken
	TextureSpec texSpecs2[] = {
		{ &self->redtoken, "Assets/redtoken.png" },
	};
    //Affiche yellowtoken
    TextureSpec texSpecs3[] = {
        { &self->yellowtoken, "Assets/yellowtoken.png" },
    };
	//Affiche loose
	TextureSpec texSpecs4[] = {
        { &self->lose, "Assets/lose.png" },
    };
	//Affiche win
	TextureSpec texSpecs5[] = {
		{ &self->win, "Assets/win.png" },
	};
	//Affiche tied
	TextureSpec texSpecs6[] = {
		{&self->tied, "Assets/tied.png" },
	};	
    int texSpecCount = sizeof(texSpecs) / sizeof(TextureSpec);
	int texSpecCount2 = sizeof(texSpecs2) / sizeof(TextureSpec);
    int texSpecCount3 = sizeof(texSpecs3) / sizeof(TextureSpec);
	int texSpecCount4 = sizeof(texSpecs4) / sizeof(TextureSpec);
	int texSpecCount5 = sizeof(texSpecs5) / sizeof(TextureSpec);
	int texSpecCount6 = sizeof(texSpecs6) / sizeof(TextureSpec);
    

    for (int i = 0; i < texSpecCount; i++)
    {
        SDL_Texture **texPtr = texSpecs[i].ptr;
        char *path = texSpecs[i].path;

        *texPtr = IMG_LoadTexture(renderer, path);
        if (*texPtr == NULL)
        {
            printf("ERROR - Loading texture %s\n", path);
            printf("      - %s\n", SDL_GetError());
            assert(false);
            abort();
        }
    }
	//Affiche redtoken
	for (int i = 0; i < texSpecCount2; i++)
	{
		SDL_Texture** texPtr = texSpecs2[i].ptr;
		char* path = texSpecs2[i].path;
        
		*texPtr = IMG_LoadTexture(renderer, path);
		if (*texPtr == NULL)
		{
			printf("ERROR - Loading texture %s\n", path);
			printf("      - %s\n", SDL_GetError());
			assert(false);
			abort();
		}
	}
    //Affiche yellowtoken
    for (int i = 0; i < texSpecCount3; i++)
    {
        SDL_Texture** texPtr = texSpecs3[i].ptr;
        char* path = texSpecs3[i].path;

        *texPtr = IMG_LoadTexture(renderer, path);
        if (*texPtr == NULL)
        {
            printf("ERROR - Loading texture %s\n", path);
            printf("      - %s\n", SDL_GetError());
            assert(false);
            abort();
        }
    }
	//Affiche loose
	for (int i = 0; i < texSpecCount4; i++)
	{
		SDL_Texture** texPtr = texSpecs4[i].ptr;
        char* path = texSpecs4[i].path;
        
		*texPtr = IMG_LoadTexture(renderer, path);
		if (*texPtr == NULL)
		{
			printf("ERROR - Loading texture %s\n", path);
			printf("      - %s\n", SDL_GetError());
			assert(false);
			abort();
		}
	}
	//Affiche win
	for (int i = 0; i < texSpecCount5; i++)
	{
		SDL_Texture** texPtr = texSpecs5[i].ptr;
		char* path = texSpecs5[i].path;
        
		*texPtr = IMG_LoadTexture(renderer, path);
		if (*texPtr == NULL)
		{
			printf("ERROR - Loading texture %s\n", path);
			printf("      - %s\n", SDL_GetError());
			assert(false);
			abort();
		}
	}
	//Affiche tied
	for (int i = 0; i < texSpecCount6; i++)
	{
		SDL_Texture** texPtr = texSpecs6[i].ptr;
		char* path = texSpecs6[i].path;
			
		*texPtr = IMG_LoadTexture(renderer, path);
		if (*texPtr == NULL)
		{
			printf("ERROR - Loading texture %s\n", path);
			printf("      - %s\n", SDL_GetError());
			assert(false);
			abort();
		}
	}
	

    return self;
}

void Assets_Delete(Assets *self)
{
    if (!self) return;

    // -------------------------------------------------------------------------
    // Lib�re les textures

    SDL_Texture **texPointers[] = {
        &self->textureExample,    
    };
    
    SDL_Texture** texPointers2[] = {
		&self->redtoken,
    };

    SDL_Texture** texPointers3[] = {
        &self->yellowtoken,
    };
    
	SDL_Texture** texPointers4[] = {
		&self->lose,
	};

	SDL_Texture** texPointers5[] = {
		&self->win,
	};
	
	SDL_Texture** texPointers6[] = {
		&self->tied,
	};
	
    
    int count = sizeof(texPointers) / sizeof(SDL_Texture **);
	int count2 = sizeof(texPointers2) / sizeof(SDL_Texture**);
    int count3 = sizeof(texPointers3) / sizeof(SDL_Texture**);
	int count4 = sizeof(texPointers4) / sizeof(SDL_Texture**);
	int count5 = sizeof(texPointers5) / sizeof(SDL_Texture**);
	int count6 = sizeof(texPointers6) / sizeof(SDL_Texture**);
	

    for (int i = 0; i < count; i++)
    {
        if (*texPointers[i])
            SDL_DestroyTexture(*(texPointers[i]));
    }
	//Affiche redtoken
	for (int i = 0; i < count2; i++)
	{
		if (*texPointers2[i])
			SDL_DestroyTexture(*(texPointers2[i]));
	}

    for (int i = 0; i < count3; i++)
    {
        if (*texPointers3[i])
            SDL_DestroyTexture(*(texPointers3[i]));
    }
    
	for (int i = 0; i < count4; i++)
	{
		if (*texPointers4[i])
			SDL_DestroyTexture(*(texPointers4[i]));
	}
    
	for (int i = 0; i < count5; i++)
	{
		if (*texPointers5[i])
			SDL_DestroyTexture(*(texPointers5[i]));
	}
	
	for (int i = 0; i < count6; i++)
	{
		if (*texPointers6[i])
			SDL_DestroyTexture(*(texPointers6[i]));
	}
	

    free(self);
}
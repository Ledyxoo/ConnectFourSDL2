#include "Settings.h"
#include "Common.h"
#include "Input.h"
#include "Assets.h"
#include "Game.h"
#include "AI.h"

// IMPORTANT :
// Les librairies SDL_TTF et SDL_Mixer sont configures dans le projet mais ne
// sont pas initialises.
// Vous devez pour cela modifier les fonctions App_Init() et App_Quit() dans
// le fichier Common.c

void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(int argc, char *argv[])
{
    (void)argc; (void)argv;

    // Initialisation de la SDL
    App_Init(SDL_INIT_VIDEO, IMG_INIT_PNG);

    // Cre la fentre et le moteur de rendu
    int sdlFlags = 0;
#ifdef FULLSCREEN
    sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
#endif

    SDL_Window *window = SDL_CreateWindow(
        u8"Connect Four", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, sdlFlags
    );

    if (!window)
    {
        printf("ERROR - Create window %s\n", SDL_GetError());
        assert(false); abort();
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    if (!renderer)
    {
        printf("ERROR - Create renderer %s\n", SDL_GetError());
        assert(false); abort();
    }

    // Cre le temps global du jeu
    g_time = Timer_New();
    AssertNew(g_time);

    // Cre le gestionnaire des entres utilisateur
    Input *input = Input_New();

    // Chargement des assets
    Assets *assets = Assets_New(renderer);
    Game* game = Game_New();
    int stdinResult = 0;
    
    //Demande  l'utilisateur si il veut jouer avec l'IA ou non
    while (stdinResult != 1 && stdinResult != 2)
    {
        printf("Bonjour bienvenue sur le puissance 4, voulez vous jouer contre l'IA ? (1 = Oui, 2 = Non) : \n");
        puts("Pour jouer utilisez les chiffres de 0 a 6 pour choisir la colonne\n");
        puts("Bonne chance !");
        (void)scanf("%d", &stdinResult);
		clean_stdin();
    }

    // Boucle principale
    bool quit = false;
    while (!quit)
    {
        // Met  jour le temps
        Timer_Update(g_time);

        // Met  jour les entres
        Input_Update(input);
       
        if (input->quitPressed)
            break;

        // Logique de jeu (seulement si la partie est en cours)
        if (Game_GetState(game) == GAME_IN_PROGRESS)
        {
            if (stdinResult == 1 && (Game_GetPlayerID(game) == PLAYER_2))
            {
                int column = AI_ComputeMove(game, true);
                printf("L'IA a choisi la colonne %d\n", column);
                Game_PlayTurn(game, column);
            }
            else
            {
                int column = -1;
                if (input->a) column = 0;
                else if (input->z) column = 1;
                else if (input->e) column = 2;
                else if (input->r) column = 3;
                else if (input->t) column = 4;
                else if (input->y) column = 5;
                else if (input->u) column = 6;

                if (column != -1)
                {
                    if (Game_CanPlayAt(game, column))
                    {
                        Game_PlayTurn(game, column);
                        printf("Tu as joue la colonne : %d\n", column);
                    }
                    else 
                    {
                        printf("Colonne %d pleine ou invalide\n", column);
                    }
                }
            }
        }

        // Efface le rendu prcdent
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        // Rendu de la grille
        SDL_FRect dstRect;
        dstRect.x = 0.0f;
        dstRect.y = 0.0f;
        dstRect.w = (float)HD_WIDTH;
        dstRect.h = (float)HD_HEIGHT;
        SDL_RenderCopyF(renderer, assets->textureExample, NULL, &dstRect);
        
        // Rendu des pions
        for (int i = 0; i < GRID_H; i++)
        {
            for (int j = 0; j < GRID_W; j++)
            {
                SDL_FRect dstRect2;
                dstRect2.x = 21.0f + j * 123.0f;
                dstRect2.y = 657.0f - (i * 125.0f);
                dstRect2.w = 106.0f;
                dstRect2.h = 106.0f;
                
                if (game->grid[i][j] == PLAYER_1)
                    SDL_RenderCopyF(renderer, assets->redtoken, NULL, &dstRect2);
                else if (game->grid[i][j] == PLAYER_2)
                    SDL_RenderCopyF(renderer, assets->yellowtoken, NULL, &dstRect2);
            }
        }

        // Affichage des messages de fin
        int state = Game_GetState(game);
        if (state != GAME_IN_PROGRESS)
        {
            SDL_FRect resRect;
            resRect.x = 50.0f;
            resRect.y = 50.0f;
            resRect.w = 800.0f;
            resRect.h = 450.0f;

            if (state == GAME_P1_WON)
            {
                SDL_RenderCopyF(renderer, assets->win, NULL, &resRect);
            }
            else if (state == GAME_P2_WON)
            {
                if (stdinResult == 1) SDL_RenderCopyF(renderer, assets->lose, NULL, &resRect);
                else SDL_RenderCopyF(renderer, assets->win, NULL, &resRect);
            }
            else if (state == GAME_IS_TIED)
            {
                SDL_RenderCopyF(renderer, assets->tied, NULL, &resRect);
            }
            
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            quit = true; // Fin du jeu après affichage du résultat
        }
        else
        {
            SDL_RenderPresent(renderer);
        }
    }

    // Libration de la mmoire
    Game_Delete(game);
    Assets_Delete(assets);
    Input_Delete(input);
    Timer_Delete(g_time);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    App_Quit();

    return EXIT_SUCCESS;
}

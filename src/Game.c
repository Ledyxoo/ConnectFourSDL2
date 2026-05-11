#include "Game.h"
#include "Input.h"
#include "Settings.h"
#include "Assets.h"

Game* Game_New()
{
    Game* self = (Game*)calloc(1, sizeof(Game));
    AssertNew(self);

    self->state = GAME_IN_PROGRESS;
    self->playerID = PLAYER_1;
    return self;
}

void Game_Delete(Game* self)
{
    if (!self) return;
    free(self);
}

Game* Game_Copy(Game* self)
{
    Game* copy = Game_New();
    *copy = *self;
    return copy;
}

/// @brief Met  jour l'tat de la partie.
/// Cette mthode est appele par Game_PlayTurn().
/// @param self la partie.
void Game_UpdateState(Game* self)
{
    assert(self);
    int i, j, k;
    CellState player;
    // Vrifiez tous les alignements de 4 colonnes
    for (i = 0; i < GRID_H; i++) 
    {
        for (j = 0; j < GRID_W - 3; j++) 
        {
            player = self->grid[i][j];
            if (player == CELL_EMPTY) continue;
            for (k = 1; k < 4; k++) 
                if (self->grid[i][j + k] != (int)player) break;
            if (k == 4) 
            {
                self->state = ((int)player == (int)PLAYER_1) ? GAME_P1_WON : GAME_P2_WON;
                return;
            }
        }
    }
    // Vrifiez tous les alignements de 4 lignes
    for (i = 0; i < GRID_H - 3; i++) 
    {
        for (j = 0; j < GRID_W; j++) 
        {
            player = self->grid[i][j];
            if (player == CELL_EMPTY) continue;
            for (k = 1; k < 4; k++)
            {
                if (self->grid[i + k][j] != (int)player) break;
            }
            if (k == 4) 
            {
                self->state = ((int)player == (int)PLAYER_1) ? GAME_P1_WON : GAME_P2_WON;
                return;
            }
        }
    }
    // Vrifiez tous les alignements de 4 diagonales (ascendantes)
    for (i = 3; i < GRID_H; i++) 
    {
        for (j = 0; j < GRID_W - 3; j++) 
        {
            player = self->grid[i][j];
            if (player == CELL_EMPTY) continue;
            for (k = 1; k < 4; k++) 
            {
                if (self->grid[i - k][j + k] != (int)player) break;
            }
            if (k == 4) 
            {
                self->state = ((int)player == (int)PLAYER_1) ? GAME_P1_WON : GAME_P2_WON;
                return;
            }
        }
    }
    // Vrifiez tous les alignements de 4 diagonales (descendantes)
    for (i = 3; i < GRID_H; i++) 
    {
        for (j = 3; j < GRID_W; j++) 
        {
            player = self->grid[i][j];
            if (player == CELL_EMPTY) continue;
            for (k = 1; k < 4; k++) {
                if (self->grid[i - k][j - k] != (int)player) break;
            }
            if (k == 4) 
            {
                self->state = ((int)player == (int)PLAYER_1) ? GAME_P1_WON : GAME_P2_WON;
                return;
            }
        }
    }
    //On vrifie si il y a des cases vident
    for (i = 0; i < GRID_H; i++) {
        for (j = 0; j < GRID_W; j++) {
            if (self->grid[i][j] == (int)CELL_EMPTY) return;
        }
    }
	//Si tout la grille est pleine game nul
    self->state = GAME_IS_TIED;
}

bool Game_CanPlayAt(Game* self, int column)
{
    assert(self);
    // TODO : Implmentez cette fonction.
    //        Retournez false si l'indice de la colonne n'est pas valide, si la colonne est dj remplie ou si la partie est dj termine.
    //        Retournez true autrement.
    if (column < 0 || column >= GRID_W) return false;
    if (self->grid[GRID_H - 1][column] == (int)CELL_EMPTY) return true;
    if (self->state == GAME_P1_WON || self->state == GAME_P2_WON || self->state == GAME_IS_TIED) return false;
    return false;
}

void Game_PlayTurn(Game* self, int column)
{
    assert(self);
    assert(Game_CanPlayAt(self, column));
    // TODO : Effectuez l'action du joueur self->playerID
    int i;
    for (i = 0; i < GRID_H; i++)
    {
        if (self->grid[i][column] == (int)CELL_EMPTY)
        {
            self->grid[i][column] = self->playerID;
			break;
			
        }

    }
    // Mettez  jour l'tat de la partie
    Game_UpdateState(self);

    // Passez au joueur suivant
    self->playerID = PlayerID_GetOther(self->playerID);
}

void Game_Print(Game* self)
{
    // TODO : Implmentez un bel affichage de la partie
    char J1 = 'X';
    char J2 = 'O';
    printf("   0   1   2   3   4   5   6\n");
    for (int i = 5; i >= 0; i--)
    {
        printf(" -----------------------------\n");
        printf("|");
        for (int j = 0; j < GRID_W; j++)
        {
            printf(" %c |", (self->grid[i][j] == (int)PLAYER_1) ? J1 : (self->grid[i][j] == (int)PLAYER_2) ? J2 : ' ');
        }
        printf("\n");
    }
    printf(" -----------------------------\n");
}

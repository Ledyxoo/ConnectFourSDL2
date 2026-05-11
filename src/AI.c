#include "AI.h"



INLINE int Int_Max(int a, int b) { return a > b ? a : b; }
INLINE int Int_Min(int a, int b) { return a < b ? a : b; }

int Game_Eval(Game* self, int playerID)
{

	// TODO : Implémentez votre fonction d'évaluation ici.
	// Si la partie est en faveur du joueur playerID, le score est positif.
	// Si elle est en faveur de l'autre joueur, le score est négatif.
	// Cette fonction est appelée par AINode_NewMinMax() pour initialiser
	// les scores des feuilles de l'arbre MinMax.
	
	int score = 0, i, j;

	for (i = 0; i < GRID_H - 1; i++)
	{
		for (j = 0; j < GRID_W - 1; j++)

		{
			if (self->grid[i][j] == playerID && self->grid[i][j + 1] == playerID)
			{
				score += 1;
			}
			if (self->grid[i][j] == playerID && self->grid[i + 1][j] == playerID)
			{
				score += 1;
			}
			if (self->grid[i][j] == playerID && self->grid[i + 1][j + 1] == playerID)
			{
				score += 1;
			}
			if (self->grid[i][j] == !playerID && self->grid[i][j + 1] == !playerID)
			{
				score -= 1;
			}
			if (self->grid[i][j] == !playerID && self->grid[i + 1][j] == !playerID)
			{
				score -= 1;
			}
			if (self->grid[i][j] == !playerID && self->grid[i + 1][j + 1] == !playerID)
			{
				score -= 1;
			}
			if (self->grid[i][j] == playerID && self->grid[i][j + 1] == playerID && self->grid[i][j + 2] == playerID)
			{
				score += 1;
			}
			if (self->grid[i][j] == playerID && self->grid[i + 1][j] == playerID && self->grid[i + 2][j] == playerID)
			{
				score += 1;
			}
			if (self->grid[i][j] == playerID && self->grid[i + 1][j + 1] == playerID && self->grid[i + 2][j + 2] == playerID)
			{
				score += 1;
			}
			if (self->grid[i][j] == !playerID && self->grid[i][j + 1] == !playerID && self->grid[i][j + 2] == !playerID)
			{
				score -= 1;
			}
			if (self->grid[i][j] == !playerID && self->grid[i + 1][j] == !playerID && self->grid[i + 2][j] == !playerID)
			{
				score -= 1;
			}
			if (self->grid[i][j] == !playerID && self->grid[i + 1][j + 1] == !playerID && self->grid[i + 2][j + 2] == !playerID)
			{
				score -= 1;
			}
			
			

		}
	}
	
	for (i = 0; i < GRID_H - 4; i++)
	{
		for (j = 0; j < GRID_W - 4; j++)

		{
			if (self->grid[i][j] == playerID && self->grid[i][j + 1] == playerID && self->grid[i][j + 2] == playerID && self->grid[i][j + 3] == playerID && self->grid[i][j + 4] == playerID)
			{
				score += 2;
			}
			if (self->grid[i][j] == playerID && self->grid[i + 1][j] == playerID && self->grid[i + 2][j] == playerID && self->grid[i + 3][j] == playerID && self->grid[i + 4][j] == playerID)
			{
				score += 2;
			}
			if (self->grid[i][j] == playerID && self->grid[i + 1][j + 1] == playerID && self->grid[i + 2][j + 2] == playerID && self->grid[i + 3][j + 3] == playerID && self->grid[i + 4][j + 4] == playerID)
			{
				score += 2;
			}
			if (self->grid[i][j] == !playerID && self->grid[i][j + 1] == !playerID && self->grid[i][j + 2] == !playerID && self->grid[i][j + 3] == !playerID && self->grid[i][j + 4] == !playerID)
			{
				score -= 2;
			}
			if (self->grid[i][j] == !playerID && self->grid[i + 1][j] == !playerID && self->grid[i + 2][j] == !playerID && self->grid[i + 3][j] == !playerID && self->grid[i + 4][j] == !playerID)
			{
				score -= 2;
			}
			if (self->grid[i][j] == !playerID && self->grid[i + 1][j + 1] == !playerID && self->grid[i + 2][j + 2] == !playerID && self->grid[i + 3][j + 3] == !playerID && self->grid[i + 4][j + 4] == !playerID)
			{
				score -= 3;
			}

		}
	}
	return score;
}

/// @brief Détruit récursivement un noeud et tous ses sous-arbres.
/// @param self le noeud.
void AINode_DeleteRec(AINode* self)
{
	/////////
	// TODO : Implémentez la destruction du noeud et de ses enfants
	// Pensez également à détruire la copie de la partie de chaque noeud.

	if (!self) return;

	int i;
	for (i = 0; i < GRID_W; i++) {
		AINode_DeleteRec(self->children[i]);
	}
	Game_Delete(self->gameState);
	free(self);
}

/// @brief Crée un noeud de l'arbre de l'algorithme MinMax.
/// Cette méthode est appelée par AITree_NewMinMax().
/// @param game la partie associée au noeud.
/// @param depth la hauteur maximale du noeud.
/// @param minLayer indique si le noeud est un noeud MIN.
/// @param playerID identifiant du joueur dont l'algorithme calcule l'action.
/// @return Le noeud créé (et initialisé).
AINode* AINode_NewMinMax(Game* game, int depth, bool minLayer, int playerID, int alpha, int beta)
{
	//Appel recursif construit l'arbre et retourn max et min des feuilles de l'arbre (minmax) en appelant la fonction d'evaluation de la partie (game_eval) pour chaque feuille de l'arbre (minmax) 
	// TODO : Implémentez la création d'un noeud de l'arbre MinMax.
	AINode* node = (AINode*)calloc(1, sizeof(AINode));
	AssertNew(node);

	node->gameState = game;
	
	if (Game_GetState(game) != GAME_IN_PROGRESS)
	{
		// autres cas
		if (Game_GetState(game) == GAME_P2_WON && (playerID == PLAYER_2))
		{
			node->score = 100;
			/*return node;*/
		}
		else if (Game_GetState(game) == GAME_P1_WON && (playerID == PLAYER_1))
		{
			node->score = 100;
			/*return node;*/
		}
		else if (Game_GetState(game) == GAME_P2_WON && (playerID == PLAYER_1))
		{
			node->score = -100;
			/*return node;*/
		}
		else if (Game_GetState(game) == GAME_P1_WON && (playerID == PLAYER_2))
		{
			node->score = -100;
			/*return node;*/
		}
		else if (Game_GetState(game) == GAME_IS_TIED)
		{
			node->score = 0;
		}
		else
		{
			assert(false);
		}

	}
	if (depth <= 0)
	{
		node->score = Game_Eval(game, playerID);
		return node;
	}
	node->score = (minLayer) ? +10000 : -10000;
	node->move = -100;

	for (int i = 0; i < GRID_W; i++)
	{
		if (Game_CanPlayAt(game, i))
		{
			Game* gameCopy = Game_Copy(game);
			Game_PlayTurn(gameCopy, i);
			node->children[i] = AINode_NewMinMax(gameCopy, depth - 1, !minLayer, playerID, alpha, beta);

			if (minLayer)
			{
				if (node->children[i]->score <= node->score)
				{
					node->score = node->children[i]->score;
					node->move = i;
				}
				beta = Int_Min(beta, node->score);
			}
			else if (!minLayer)
			{
				if (node->children[i]->score >= node->score)
				{
					node->score = node->children[i]->score;
					node->move = i;
				}
				beta = Int_Max(beta, node->score);
			}
		}
		AINode_DeleteRec(node->children[i]);
		node->children[i] = NULL;

		if (alpha >= beta)
		{
			return node;
		}
	}
	return node;
}

AITree* AITree_NewMinMax(Game* game, int depth, int playerID)
{
	AITree* self = (AITree*)calloc(1, sizeof(AITree));
	AssertNew(self);

	Game* curGame = Game_Copy(game);
	self->root = AINode_NewMinMax(curGame, depth, false, playerID, -1000, +1000);

	return self;
}

void AITree_Delete(AITree* self)
{
	if (!self) return;
	AINode_DeleteRec(self->root);
	free(self);
}

int AI_ComputeMove(Game* game, int playerID)
{
	/////////
	// TODO : Cette fonction représente votre IA.
	// Modifiez-la comme vous le souhaitez.
	int depth = 2;
	AITree* tree = AITree_NewMinMax(game, depth, playerID);
	int move = tree->root->move;
	AITree_Delete(tree);

	return move;

}
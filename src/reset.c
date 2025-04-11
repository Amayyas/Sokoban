/*
** EPITECH PROJECT, 2025
** Sokoban
** File description:
** reset
*/

#include "sokoban.h"

void free_map_recursive(game_t *game, int i)
{
    if (!game || i >= game->height)
        return;
    if (game->grid && game->grid[i])
        free(game->grid[i]);
    if (game->original && game->original[i])
        free(game->original[i]);
    free_map_recursive(game, i + 1);
}

void free_map(game_t *game)
{
    if (!game)
        return;
    free_map_recursive(game, 0);
    if (game->grid)
        free(game->grid);
    if (game->original)
        free(game->original);
    free(game);
}

void reset_position_recursive(game_t *game, int i, int j)
{
    if (i >= game->height)
        return;
    if (j >= game->width) {
        reset_position_recursive(game, i + 1, 0);
        return;
    }
    game->grid[i][j] = game->original[i][j];
    if (game->grid[i][j] == PLAYER) {
        game->player.x = j;
        game->player.y = i;
    }
    reset_position_recursive(game, i, j + 1);
}

void reset_game(game_t *game)
{
    reset_position_recursive(game, 0, 0);
    count_elements(game);
}

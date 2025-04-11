/*
** EPITECH PROJECT, 2025
** Sokoban
** File description:
** count_elements
*/

#include "sokoban.h"

static void count_elements_recursive(game_t *game, int i, int j)
{
    if (i >= game->height)
        return;
    if (j >= game->width) {
        count_elements_recursive(game, i + 1, 0);
        return;
    }
    if (game->grid[i][j] == BOX)
        game->box_count++;
    if (game->grid[i][j] == STORAGE)
        game->storage_count++;
    if (game->grid[i][j] == PLAYER) {
        game->player.x = j;
        game->player.y = i;
    }
    count_elements_recursive(game, i, j + 1);
}

void count_elements(game_t *game)
{
    game->box_count = 0;
    game->storage_count = 0;
    game->boxes_on_target = 0;
    count_elements_recursive(game, 0, 0);
}

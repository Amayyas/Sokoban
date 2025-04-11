/*
** EPITECH PROJECT, 2025
** Sokoban
** File description:
** check
*/

#include "sokoban.h"

static int check_char_recursive(game_t *game, int i, int j)
{
    char c = game->grid[i][j];

    if (c != WALL && c != PLAYER && c != BOX &&
        c != STORAGE && c != EMPTY && c != '\n')
        return 1;
    if (j + 1 < game->width)
        return check_char_recursive(game, i, j + 1);
    if (i + 1 < game->height)
        return check_char_recursive(game, i + 1, 0);
    return 0;
}

int check_characters(game_t *game)
{
    return check_char_recursive(game, 0, 0);
}

static int count_players_recursive(game_t *game, int i, int j, int count)
{
    if (game->grid[i][j] == PLAYER)
        count++;
    if (j + 1 < game->width)
        return count_players_recursive(game, i, j + 1, count);
    if (i + 1 < game->height)
        return count_players_recursive(game, i + 1, 0, count);
    return count;
}

int check_player_count(game_t *game)
{
    int player_count = count_players_recursive(game, 0, 0, 0);

    return player_count != 1;
}

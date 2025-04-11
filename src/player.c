/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Player movement functions for the my_sokoban project
*/

#include "sokoban.h"

int can_move_box(game_t *game, int dx, int dy)
{
    int box_x = game->player.x + dx;
    int box_y = game->player.y + dy;
    int dest_x = box_x + dx;
    int dest_y = box_y + dy;
    char dest_cell = game->grid[dest_y][dest_x];

    if (dest_cell == WALL || dest_cell == BOX || dest_cell == BOX_ON_STORAGE)
        return 0;
    return 1;
}

static void count_boxes_recursive(game_t *game, int i, int j)
{
    if (i >= game->height)
        return;
    if (game->grid[i][j] == BOX_ON_STORAGE)
        game->boxes_on_target++;
    if (j + 1 < game->width)
        count_boxes_recursive(game, i, j + 1);
    else
        count_boxes_recursive(game, i + 1, 0);
}

void update_boxes_on_target(game_t *game)
{
    game->boxes_on_target = 0;
    count_boxes_recursive(game, 0, 0);
}

static void handle_box_movement(game_t *game, int dx, int dy)
{
    int box_x = game->player.x + 2 * dx;
    int box_y = game->player.y + 2 * dy;

    if (game->grid[box_y][box_x] == STORAGE)
        game->grid[box_y][box_x] = BOX_ON_STORAGE;
    else
        game->grid[box_y][box_x] = BOX;
}

static void update_player_position(game_t *game, int dx, int dy)
{
    int x = game->player.x;
    int y = game->player.y;
    int new_x = x + dx;
    int new_y = y + dy;
    char current_cell = game->grid[y][x];
    char next_cell = game->grid[new_y][new_x];

    if (next_cell == BOX_ON_STORAGE || next_cell == STORAGE)
        game->grid[new_y][new_x] = PLAYER_ON_STORAGE;
    else
        game->grid[new_y][new_x] = PLAYER;
    if (current_cell == PLAYER_ON_STORAGE)
        game->grid[y][x] = STORAGE;
    else
        game->grid[y][x] = EMPTY;
    game->player.x = new_x;
    game->player.y = new_y;
}

void move_player(game_t *game, int dx, int dy)
{
    int new_x = game->player.x + dx;
    int new_y = game->player.y + dy;
    char next_cell;

    if (new_x < 0 || new_x >= game->width || new_y < 0 ||
        new_y >= game->height)
        return;
    next_cell = game->grid[new_y][new_x];
    if (next_cell == WALL)
        return;
    if (next_cell == BOX || next_cell == BOX_ON_STORAGE) {
        if (!can_move_box(game, dx, dy))
            return;
        handle_box_movement(game, dx, dy);
    }
    update_player_position(game, dx, dy);
    update_boxes_on_target(game);
}

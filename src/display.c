/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Display functions for the my_sokoban project
*/

#include "sokoban.h"

void display_resize_message(void)
{
    clear();
    mvprintw(LINES / 2, (COLS - 24) / 2, "Terminal too small!");
    refresh();
}

int check_terminal_size(game_t *game)
{
    if (COLS < game->width || LINES < game->height) {
        display_resize_message();
        return 0;
    }
    return 1;
}

void display_map(game_t *game)
{
    int i;
    int j;
    int start_y = (LINES - game->height) / 2;
    int start_x = (COLS - game->width) / 2;
    char c;

    clear();
    for (i = 0; i < game->height; i++) {
        for (j = 0; j < game->width; j++) {
            c = game->grid[i][j];
            mvaddch(start_y + i, start_x + j, c);
        }
    }
    mvprintw(1, 1, "Boxes on target: %d/%d",
        game->boxes_on_target, game->box_count);
    mvprintw(2, 1, "Press SPACE to reset, ESC to quit");
    refresh();
}

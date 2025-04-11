/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Game functions for the my_sokoban project
*/

#include "sokoban.h"

void init_game(void)
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    timeout(100);
}

void end_game(void)
{
    endwin();
}

int check_win(game_t *game)
{
    return (game->boxes_on_target == game->box_count);
}

static int is_box_stuck(game_t *game, int i, int j)
{
    if ((game->grid[i - 1][j] == WALL || game->grid[i + 1][j] == WALL) &&
        (game->grid[i][j - 1] == WALL || game->grid[i][j + 1] == WALL))
        return 1;
    if ((game->grid[i - 1][j] == WALL && game->grid[i][j - 1] == WALL) ||
        (game->grid[i - 1][j] == WALL && game->grid[i][j + 1] == WALL) ||
        (game->grid[i + 1][j] == WALL && game->grid[i][j - 1] == WALL) ||
        (game->grid[i + 1][j] == WALL && game->grid[i][j + 1] == WALL))
        return 1;
    return 0;
}

static int count_stuck_boxes(game_t *game, int i, int j, int *stuck_boxes)
{
    if (i >= game->height)
        return *stuck_boxes;
    if (j >= game->width)
        return count_stuck_boxes(game, i + 1, 0, stuck_boxes);
    if (game->grid[i][j] == BOX && is_box_stuck(game, i, j))
        (*stuck_boxes)++;
    return count_stuck_boxes(game, i, j + 1, stuck_boxes);
}

int check_deadlock(game_t *game)
{
    int stuck_boxes = 0;

    count_stuck_boxes(game, 0, 0, &stuck_boxes);
    return (stuck_boxes == game->box_count &&
            game->boxes_on_target < game->box_count);
}

static void handle_player_movement(game_t *game, int ch)
{
    switch (ch) {
        case KEY_UP:
            move_player(game, 0, -1);
            break;
        case KEY_DOWN:
            move_player(game, 0, 1);
            break;
        case KEY_LEFT:
            move_player(game, -1, 0);
            break;
        case KEY_RIGHT:
            move_player(game, 1, 0);
            break;
    }
}

static int check_game_state(game_t *game)
{
    if (check_win(game)) {
        display_map(game);
        napms(500);
        return 0;
    }
    if (check_deadlock(game)) {
        display_map(game);
        napms(500);
        return 1;
    }
    return -1;
}

static void process_input(game_t *game, int *game_running)
{
    int ch = getch();

    if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
        handle_player_movement(game, ch);
    if (ch == ' ')
        reset_game(game);
    if (ch == 27)
        *game_running = 0;
}

int play_game(game_t *game)
{
    int game_running = 1;
    int game_state;

    while (game_running) {
        if (check_terminal_size(game))
            display_map(game);
        process_input(game, &game_running);
        game_state = check_game_state(game);
        if (game_state != -1)
            return game_state;
    }
    return 0;
}

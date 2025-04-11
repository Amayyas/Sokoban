/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Header for the my_sokoban project
*/

#ifndef SOKOBAN_H_
    #define SOKOBAN_H_

    #include <ncurses.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/stat.h>

    #define PLAYER 'P'
    #define BOX 'X'
    #define STORAGE 'O'
    #define WALL '#'
    #define EMPTY ' '
    #define BOX_ON_STORAGE '*'
    #define PLAYER_ON_STORAGE '+'

    #define ERROR_CODE 84

typedef struct {
    int x;
    int y;
} position_t;

typedef struct {
    char **grid;
    char **original;
    int width;
    int height;
    position_t player;
    int box_count;
    int storage_count;
    int boxes_on_target;
} game_t;

int check_characters(game_t *game);
int check_player_count(game_t *game);

void count_elements(game_t *game);

void display_resize_message(void);
int check_terminal_size(game_t *game);
void display_map(game_t *game);

void init_game(void);
void end_game(void);
int check_win(game_t *game);
int check_deadlock(game_t *game);
int play_game(game_t *game);

void print_usage(void);
void handle_error(const char *message);
int parse_arguments(int argc, char **argv);
int main(int argc, char **argv);

int allocate_grid_rows(char **grid, int width, int height);
void fill_grid_content(char **grid, char *file_content, int width);
game_t *load_map(char *filepath);
int validate_map(game_t *game);

int can_move_box(game_t *game, int dx, int dy);
void update_boxes_on_target(game_t *game);
void move_player(game_t *game, int dx, int dy);

void free_map_recursive(game_t *game, int i);
void free_map(game_t *game);
void reset_position_recursive(game_t *game, int i, int j);
void reset_game(game_t *game);

int count_lines(char *file_content);
int get_max_line_length(char *file_content);
char **create_grid(char *file_content, int width, int height);
char **make_map_from_string(char *map_str, int *width, int *height);

#endif /* !SOKOBAN_H_ */

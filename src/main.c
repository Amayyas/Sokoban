/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Main file for the my_sokoban project
*/

#include "sokoban.h"

void print_usage(void)
{
    printf("USAGE\n");
    printf("\t./my_sokoban map\n");
    printf("DESCRIPTION\n");
    printf("\tmap\tfile representing the warehouse map, containing");
    printf(" '#' for walls,");
    printf(" 'P' for the player, 'X' for boxes and 'O' for storage");
    printf(" locations.\n");
}

void handle_error(const char *message)
{
    write(2, "Error: ", 7);
    write(2, message, strlen(message));
    write(2, "\n", 1);
    exit(ERROR_CODE);
}

int parse_arguments(int argc, char **argv)
{
    if (argc != 2) {
        print_usage();
        return ERROR_CODE;
    }
    if (strcmp(argv[1], "-h") == 0) {
        print_usage();
        return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    game_t *game = NULL;
    int result = 0;
    int arg_check = parse_arguments(argc, argv);

    if (arg_check != 1)
        return arg_check;
    game = load_map(argv[1]);
    if (!game)
        return ERROR_CODE;
    if (validate_map(game) != 0) {
        free_map(game);
        handle_error("Invalid map");
    }
    init_game();
    result = play_game(game);
    end_game();
    free_map(game);
    return result;
}

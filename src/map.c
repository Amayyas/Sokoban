/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Map handling functions for the my_sokoban project
*/

#include "sokoban.h"

static int allocate_grid_row(char **grid, int width, int height, int i)
{
    if (i >= height)
        return 1;
    grid[i] = malloc(sizeof(char) * (width + 1));
    if (!grid[i])
        return 0;
    memset(grid[i], ' ', width);
    grid[i][width] = '\0';
    if (allocate_grid_row(grid, width, height, i + 1))
        return 1;
    free(grid[i]);
    return 0;
}

int allocate_grid_rows(char **grid, int width, int height)
{
    return allocate_grid_row(grid, width, height, 0);
}

void fill_grid_content(char **grid, char *file_content, int width)
{
    int i = 0;
    int j;
    char *line_start = file_content;

    while (*line_start) {
        j = 0;
        while (*line_start && *line_start != '\n' && j < width) {
            grid[i][j] = *line_start;
            line_start++;
            j++;
        }
        if (*line_start == '\n')
            line_start++;
        i++;
    }
}

static int open_and_get_file_size(const char *filepath, int *file_size)
{
    struct stat st;
    int fd;

    if (stat(filepath, &st) == -1) {
        handle_error("Cannot access map file");
        return -1;
    }
    *file_size = st.st_size;
    fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        handle_error("Cannot open map file");
        return -1;
    }
    return fd;
}

static char *read_file_content(const char *filepath, int *file_size)
{
    int fd = open_and_get_file_size(filepath, file_size);
    char *file_content;

    if (fd == -1)
        return NULL;
    file_content = malloc(sizeof(char) * (*file_size + 1));
    if (!file_content) {
        close(fd);
        return NULL;
    }
    if (read(fd, file_content, *file_size) == -1) {
        handle_error("Cannot read map file");
        close(fd);
        free(file_content);
        return NULL;
    }
    file_content[*file_size] = '\0';
    close(fd);
    return file_content;
}

static game_t *create_game_structure(char *file_content, int file_size)
{
    game_t *game = malloc(sizeof(game_t));

    (void)file_size;
    if (!game)
        return NULL;
    game->height = count_lines(file_content) + 1;
    game->width = get_max_line_length(file_content);
    game->grid = create_grid(file_content, game->width, game->height);
    game->original = create_grid(file_content, game->width, game->height);
    if (!game->grid || !game->original) {
        free_map(game);
        return NULL;
    }
    count_elements(game);
    return game;
}

game_t *load_map(char *filepath)
{
    game_t *game;
    char *file_content;
    int file_size;

    file_content = read_file_content(filepath, &file_size);
    if (!file_content)
        return NULL;
    game = create_game_structure(file_content, file_size);
    free(file_content);
    return game;
}

int validate_map(game_t *game)
{
    if (check_characters(game))
        return 1;
    if (check_player_count(game))
        return 1;
    if (game->box_count == 0 || game->storage_count == 0)
        return 1;
    if (game->box_count != game->storage_count)
        return 1;
    return 0;
}

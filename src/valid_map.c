/*
** EPITECH PROJECT, 2025
** Sokoban
** File description:
** valid_map
*/

#include "sokoban.h"

int count_lines(char *file_content)
{
    int count = 0;
    char *tmp = file_content;

    while (*tmp) {
        if (*tmp == '\n')
            count++;
        tmp++;
    }
    return count;
}

static int max_int(int a, int b)
{
    return (a > b) ? a : b;
}

static int get_line_length_recursive(char *str, int current_len)
{
    if (!(*str))
        return current_len;
    if (*str == '\n')
        return current_len;
    return get_line_length_recursive(str + 1, current_len + 1);
}

static int get_max_line_length_recursive(char *str, int max_len)
{
    int line_len;

    if (!(*str))
        return max_len;
    line_len = get_line_length_recursive(str, 0);
    max_len = max_int(max_len, line_len);
    return get_max_line_length_recursive(str + line_len +
        (*str == '\n' ? 1 : 0), max_len);
}

int get_max_line_length(char *file_content)
{
    return get_max_line_length_recursive(file_content, 0);
}

char **create_grid(char *file_content, int width, int height)
{
    char **grid = malloc(sizeof(char *) * (height + 1));

    if (!grid)
        return NULL;
    if (!allocate_grid_rows(grid, width, height)) {
        free(grid);
        return NULL;
    }
    fill_grid_content(grid, file_content, width);
    grid[height] = NULL;
    return grid;
}

char **make_map_from_string(char *map_str, int *width, int *height)
{
    *height = count_lines(map_str) + 1;
    *width = get_max_line_length(map_str);
    return create_grid(map_str, *width, *height);
}

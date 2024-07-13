#include "../maze.h"

/**
 * count_lines_in_file : Counts number of lines in a file
 * @file_path: path to file
 * Return: The number of lines in the file, or 0 if the file could not be opened
 **/
size_t count_lines_in_file(const char *file_path)
{
    FILE *file;
    char *line = NULL;
    size_t lines = 0;
    size_t line_length = 0;
    ssize_t read;

    file = fopen(file_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: File does not exist\n");
        return 0;
    }

    while ((read = getline(&line, &line_length, file)) != -1)
    {
        lines++;
    }

    fclose(file);
    free(line);

    return lines;
}

/**
 * count_chars_in_line: Counts number of characters in a string
 * @line: string to count characters in
 * Return: The number of characters in the string.
 **/
size_t count_chars_in_line(const char *line)
{
    size_t char_count = 0;

    while (line[char_count] != '\0')
    {
        char_count++;
    }

    return char_count;
}

/**
 * initialize_grid_point - Initializes a grid point in maze
 * @maze: maze grid
 * @player: player's position
 * @winning_point: winning point position
 * @current_char: current character being read
 * @maze_line: current line of maze being initialized
 * @line: current line being read
 * @found_winning_point: Flag indicating if winning point has been found
 **/
void initialize_grid_point(char **maze, double_s *player, int_s *winning_point, size_t current_char,
                           size_t maze_line, const char *line, int *found_winning_point)
{
    if (line[current_char] == 'p')
    {
        player->y = current_char;
        player->x = maze_line;
        maze[maze_line][current_char] = '0';
    }
    else if (line[current_char] == 'w')
    {
        *found_winning_point = 1;
        winning_point->y = current_char;
        winning_point->x = maze_line;
        maze[maze_line][current_char] = '0';
    }
    else
    {
        if (line[current_char] == '0' && *found_winning_point == 0)
        {
            winning_point->y = current_char;
            winning_point->x = maze_line;
        }
        maze[maze_line][current_char] = line[current_char];
    }
}

/**
 * create_maze - Creates and initializes maze from a file
 * @file_path: path to file containing maze
 * @player: player's position
 * @winning_point: winning point position
 * @maze_height: Pointer to store height of maze
 * Return: A pointer to the maze grid, or NULL if an error occurred.
 **/
char **create_maze(const char *file_path, double_s *player, int_s *winning_point, size_t *maze_height)
{
    FILE *file;
    char **maze = NULL;
    char *line = NULL;
    ssize_t read = 0;
    size_t line_count, maze_line = 0, char_count, current_char, buffer_size;
    int found_winning_point = 0;

    line_count = count_lines_in_file(file_path);
    *maze_height = line_count;

    if (line_count == 0)
    {
        return NULL;
    }

    maze = malloc(sizeof(char *) * line_count);
    if (maze == NULL)
    {
        return NULL;
    }

    file = fopen(file_path, "r");
    if (file == NULL)
    {
        free(maze);
        return NULL;
    }

    read = getline(&line, &buffer_size, file);
    while (read != -1)
    {
        char_count = count_chars_in_line(line);
        maze[maze_line] = malloc(sizeof(char) * (char_count + 1));
        if (maze[maze_line] == NULL)
        {
            for (size_t i = 0; i < maze_line; i++)
            {
                free(maze[i]);
            }
            free(maze);
            fclose(file);
            free(line);
            return NULL;
        }

        for (current_char = 0; current_char < char_count; current_char++)
        {
            initialize_grid_point(maze, player, winning_point, current_char, maze_line, line, &found_winning_point);
        }

        maze_line++;
        read = getline(&line, &buffer_size, file);
    }

    fclose(file);
    free(line);

    return maze;
}

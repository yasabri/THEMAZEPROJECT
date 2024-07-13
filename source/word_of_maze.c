#include "../themaze.h"

/**
 * build_levels_from_files - Constructs levels from given file paths
 * @num_of_files: Number of level files
 * @level_files: Array of file paths for the levels
 * Return: Pointer to an array of levels, or NULL if an error occurred.
 **/
level *build_levels_from_files(int num_of_files, char *level_files[])
{
    level temp_level = {NULL, 0, {0, 0}, {2, 2}, {-1, 0}, {0, 0.5}};
    level *levels;
    int x, level_index;

    levels = malloc(sizeof(level) * (num_of_files - 1));
    if (levels == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for levels\n");
        return NULL;
    }

    level_index = 0;
    for (x = 1; x < num_of_files; x++, level_index++)
    {
        temp_level.map = create_map(level_files[x], &temp_level.player_position, &temp_level.winning_position,
                                    &temp_level.height);
        if (temp_level.map == NULL)
        {
            fprintf(stderr, "Error: Failed to create map for level %d\n", x);
            for (int j = 0; j < level_index; j++)
            {
                for (size_t k = 0; k < levels[j].height; k++)
                {
                    free(levels[j].map[k]);
                }
                free(levels[j].map);
            }
            free(levels);
            return NULL;
        }
        levels[level_index] = temp_level;
    }

    return levels;
}

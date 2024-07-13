#include "../themaze.h"

/**
 * calculate_ray_direction - This function calculates the initial side distances and the direction of the ray.
 * @step: This function points to the step direction.
 * @side_distance: This function points to the next side's distance.
 * @ray_position: The ray's initial position.
 * @map_coordinate: This function determines the current map coordinates.
 * @delta_distance: The distance to the next map coordinate in the x and y direction.
 * @ray_direction: Ray's direction vector
 **/
void calculate_ray_direction(int_s *step, double_s *side_distance, double_s ray_position,
                             int_s map_coordinate, double_s delta_distance, double_s ray_direction)
{
    if (ray_direction.x < 0)
    {
        step->x = -1;
        side_distance->x = (ray_position.x - map_coordinate.x) * delta_distance.x;
    }
    else
    {
        step->x = 1;
        side_distance->x = (map_coordinate.x + 1.0 - ray_position.x) * delta_distance.x;
    }

    if (ray_direction.y < 0)
    {
        step->y = -1;
        side_distance->y = (ray_position.y - map_coordinate.y) * delta_distance.y;
    }
    else
    {
        step->y = 1;
        side_distance->y = (map_coordinate.y + 1.0 - ray_position.y) * delta_distance.y;
    }
}

/**
 * compute_wall_distance - Determines the player's distance from the wall. * * @map: The map of the game.
 * @side_distance: A reference to the side distance as of right now
 * @step: Indicates direction of step.
 * @delta_distance: delta distance is indicated by this pointer.
 * @map_coordinate: Pointer to coordinates of current map.
 * @hit_side: Indicates which side of wall was struck (x for x, y for y).
 * @ray_direction: pointer to ray's direction.
 * @ray_position: Pointer to ray's starting position.
 * Return: The player's distance from the wall.
 **/
double compute_wall_distance(char **map, double_s *side_distance, int_s *map_coordinate,
                             int_s *step, double_s *delta_distance, int *hit_side,
                             double_s *ray_direction, double_s *ray_position)
{
    double wall_distance;
    int wall_hit = 0;

    while (wall_hit == 0)
    {
        if (side_distance->x < side_distance->y)
        {
            side_distance->x += delta_distance->x;
            map_coordinate->x += step->x;
            *hit_side = 0;
        }
        else
        {
            side_distance->y += delta_distance->y;
            map_coordinate->y += step->y;
            *hit_side = 1;
        }

        if (map[map_coordinate->x][map_coordinate->y] > '0')
        {
            wall_hit = 1;
        }
    }

    if (*hit_side == 0)
    {
        wall_distance = (map_coordinate->x - ray_position->x + (1 - step->x) / 2) / ray_direction->x;
    }
    else
    {
        wall_distance = (map_coordinate->y - ray_position->y + (1 - step->y) / 2) / ray_direction->y;
    }

    return wall_distance;
}

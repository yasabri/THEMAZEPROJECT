#include "../themaze.h"

/**
 * draw - This function will render entire scene
 * @map: 2D character array representing the map
 * @instance: SDL instance used for rendering
 * @player_pos: player's starting position
 * @direction: player's direction vector
 * @camera_plane: camera plane vector
 **/
void draw(SDL_Instance instance, char **map, double_s player_pos, double_s direction,
          double_s camera_plane)
{
    draw_background(instance);
    draw_walls(map, player_pos, instance, direction, camera_plane);
    SDL_RenderPresent(instance.renderer);
}

/**
 * draw_background - Renders sky and floor background
 * @instance: SDL instance used for rendering
 **/
void draw_background(SDL_Instance instance)
{
    size_t x;

    for (x = 0; x < SCREEN_WIDTH; x++)
    {
        SDL_SetRenderDrawColor(instance.renderer, 0, 0xDD, 0xFF, 0xFF);
        SDL_RenderDrawLine(instance.renderer, x, 0, x, SCREEN_HEIGHT / 2);
        SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0, 0xFF, 0xFF);
        SDL_RenderDrawLine(instance.renderer, x, SCREEN_HEIGHT / 2, x, SCREEN_HEIGHT);
    }
}

/**
 * draw_walls - Uses raycasting to render walls
 * @map: 2D character array representing the map
 * @player_pos: player's position
 * @instance: SDL instance used for rendering
 * @direction: player's direction vector
 * @camera_plane: camera plane vector
 **/
void draw_walls(char **map, double_s player_pos, SDL_Instance instance, double_s direction,
                double_s camera_plane)
{
    double_s ray_pos, ray_dir, dist_to_side, delta_dist;
    double wall_dist, camera_x;
    int_s map_coord, step;
    int wall_height, wall_start, wall_end, screen_x, side_hit;

    for (screen_x = 0; screen_x < SCREEN_WIDTH; screen_x++)
    {
        side_hit = 0;
        camera_x = 2 * screen_x / (double)SCREEN_WIDTH - 1;
        ray_pos.x = player_pos.x;
        ray_pos.y = player_pos.y;
        ray_dir.x = direction.x + camera_plane.x * camera_x;
        ray_dir.y = direction.y + camera_plane.y * camera_x;
        map_coord.x = (int)ray_pos.x;
        map_coord.y = (int)ray_pos.y;
        delta_dist.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
        delta_dist.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));
        check_ray_dir(&step, &dist_to_side, ray_pos, map_coord, delta_dist, ray_dir);
        wall_dist = get_wall_dist(map, &dist_to_side, &map_coord, &step,
                                  &delta_dist, &side_hit, &ray_dir, &ray_pos);
        wall_height = (int)(SCREEN_HEIGHT / wall_dist);
        wall_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
        if (wall_start < 0)
            wall_start = 0;
        wall_end = wall_height / 2 + SCREEN_HEIGHT / 2;
        if (wall_end >= SCREEN_HEIGHT)
            wall_end = SCREEN_HEIGHT - 1;
        choose_color(instance, map, map_coord, side_hit);
        SDL_RenderDrawLine(instance.renderer, screen_x, wall_start, screen_x, wall_end);
    }
}

/** 
 * choose_color - Determines the color of walls to be rendered by using hit side and map data
 * @instance: SDL instance that is being rendered
 * @map: 2D character array that the map is represented by
 * @map_coord: map's current coordinate
 **/
 @side_hit: Indicates if a side was hit vertically or horizontally.
void choose_color(SDL_Instance instance, char **map, int_s map_coord, int side_hit)
{
    switch (map[map_coord.x][map_coord.y])
    {
    case '1':
        if (side_hit == 0)
            SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0, 0, 0xFF);
        else
            SDL_SetRenderDrawColor(instance.renderer, 0x88, 0, 0, 0xFF);
        break;
    case '2':
        if (side_hit == 0)
            SDL_SetRenderDrawColor(instance.renderer, 0, 0xFF, 0, 0xFF);
        else
            SDL_SetRenderDrawColor(instance.renderer, 0, 0x88, 0, 0xFF);
        break;
    case '3':
        if (side_hit == 0)
            SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0xFF, 0xFF);
        else
            SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0x88, 0xFF);
        break;
    case '4':
        if (side_hit == 0)
            SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0, 0xFF);
        else
            SDL_SetRenderDrawColor(instance.renderer, 0x88, 0x88, 0, 0xFF);
        break;
    default:
        if (side_hit == 0)
            SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        else
            SDL_SetRenderDrawColor(instance.renderer, 0x88, 0x88, 0x88, 0xFF);
        break;
    }
}

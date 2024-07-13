#include "../maze.h"

/**
 * main - Initializes and runs maze game.
 * @argv: Array of command-line arguments
 * @argc: Number of command-line arguments
 * Return: 0 on success, 1 on failure.
 **/
int main(int argc, char *argv[])
{
	SDL_Instance instance;
	level *levels;
	int current_level, win_status, num_of_levels;
	keys key_state = {0, 0, 0, 0};

	current_level = win_status = 0;
	num_of_levels = argc;
	if (num_of_levels < 2)
		return (1);
	levels = build_world_from_args(argc, argv);
	if (levels == NULL)
		return (1);
	if (initialize_instance(&instance) != 0)
		return (1);
	current_level = 0;
	while (1)
	{
		if (keyboard_events(&key_state))
		{
			free_memory(instance, levels[current_level].map, levels[current_level].height);
			break;
		}
		movement(key_state, &levels[current_level].plane, &levels[current_level].dir, &levels[current_level].play,
			 levels[current_level].map);
		if (check_win(levels[current_level].play, levels[current_level].win, &win_status))
		{
			free_map(levels[current_level].map, levels[current_level].height);
			current_level++;
			if (current_level == argc - 1)
				break;
			win_status = 0;
		}
		draw(instance, levels[current_level].map, levels[current_level].play, levels[current_level].dir,
		     levels[current_level].plane);
	}
	close_SDL(instance);
	if (win_status)
		print_win();
	return (0);
}

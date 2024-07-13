#include "../themaze.h"

/**
 * print_win - this function pops up win message for user
 **/
void print_win(void)
{
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("      /\\_/\\  Congratulations!\n");
    printf("     ( o.o )  You have won the maze game!\n");
    printf("      > ^ <  Great job!\n");
    printf("\n");
    printf("     You navigated through the maze\n");
    printf("     and reached the finish line.\n");
    printf("\n");
    printf("      \\  /   __   |   |\n");
    printf("       \\/   /  \\  |   |\n");
    printf("       /   |    |     |\n");
    printf("      /     \\__/   \\__/\n\n");
    printf("\n\n\n\n\n\n\n\n\n\n");
}
/**
 * check_win - checks if the player has reached the win spot in the maze.
 * @play: player position
 * @win_value: flag to indicate win state
 * @win: win spot coordinates
 * Return: 0 or 1
 **/
int check_win(double_s play, int_s win, int *win_value)
{
	if ((int) play.x == win.x && (int) play.y == win.y)
	{
		*win_value = 1;
		return (1);
	}
	return (0);
}


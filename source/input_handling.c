#include "../themaze.h"

/**
 * check_key_release_events - Handles key release events
 * @event: SDL event containing key release data
 * @key_states: structure storing state of keys
 **/
void check_key_release_events(SDL_Event event, keys *key_states)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        key_states->up = 0;
        break;
    case SDLK_DOWN:
        key_states->down = 0;
        break;
    case SDLK_RIGHT:
        key_states->right = 0;
        break;
    case SDLK_LEFT:
        key_states->left = 0;
        break;
    default:
        break;
    }
}

/**
 * check_key_press_events - Handles key press events
 * @event: SDL event containing the key press data
 * @key_states: The structure storing the state of the keys
 * Return: 0 if no quit event, 1 if ESC key (quit event) is pressed
 **/
int check_key_press_events(SDL_Event event, keys *key_states)
{
    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        return 1;

    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        key_states->up = 1;
        break;
    case SDLK_DOWN:
        key_states->down = 1;
        break;
    case SDLK_RIGHT:
        key_states->right = 1;
        break;
    case SDLK_LEFT:
        key_states->left = 1;
        break;
    default:
        break;
    }
    return 0;
}

/**
 * keyboard_events - Polls for keyboard events and updates key states
 * @key_states: The structure storing the state of the keys
 * Return: 0 if no quit event, 1 if a quit event is detecte
 **/
int keyboard_events(keys *key_states)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return 1;
        case SDL_KEYDOWN:
            if (check_key_press_events(event, key_states))
                return 1;
            break;
        case SDL_KEYUP:
            check_key_release_events(event, key_states);
            break;
        default:
            break;
        }
    }
    return 0;
}

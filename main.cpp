// for initializing and shutdown functions
#include <SDL2/SDL.h>

// for rendering images and graphics on screen
#include <SDL2/SDL_image.h>

// for using SDL_Delay() functions
#include <SDL2/SDL_timer.h>

int main()
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    //Initilize
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640*2,480*2, 0, &window, &renderer);
    SDL_RenderSetScale(renderer,2, 2);

    //Clear renderer
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    
    SDL_SetRenderDrawColor(renderer,0,102,0,255); //set draw color to green
    SDL_RenderDrawPoint(renderer,640/2,480/2); //draw point at the middle of the screen (it will be green becase the render draw color was set to green)


    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    return 0;
}
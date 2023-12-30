// for initializing and shutdown functions
#include <SDL2/SDL.h>

// for rendering images and graphics on screen
#include <SDL2/SDL_image.h>

// for using SDL_Delay() functions
#include <SDL2/SDL_timer.h>

#include <vector>

SDL_Event e;
SDL_Window* window;
SDL_Renderer* renderer;
std::vector<SDL_FPoint> points;


int main()
{
    // Initilization
    bool running = true;
    SDL_Event event;

    //Resolution
    int resolutionW = 640;
    int resolutionH = 480;

    //Window Init
    SDL_Init(SDL_INIT_EVERYTHING); // SDL INIT
    window = SDL_CreateWindow(  "coom", 
                                 SDL_WINDOWPOS_UNDEFINED, 
                                 SDL_WINDOWPOS_UNDEFINED,
                                 resolutionW,
                                 resolutionH,
                                 0); //I dont know if I like this formatting. Saw it in a tutorial.

    //Render Init
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    while(running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) 
            {
                running = false;
                break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}



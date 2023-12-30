// for initializing and shutdown functions
#include <SDL2/SDL.h>

// for rendering images and graphics on screen
#include <SDL2/SDL_image.h>

// for using SDL_Delay() functions
#include <SDL2/SDL_timer.h>
#include <vector>

#define windowWidth 600
#define windowHeight 480

float px, py; //player position


SDL_Event e;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* screen = NULL;
std::vector<SDL_FPoint> points;


void renderPlayer(SDL_Renderer* renderer, float px, float py) {
    SDL_Rect playerRectangle;
    playerRectangle.x = static_cast<int>(px) - 5;
    playerRectangle.y = static_cast<int>(py) + 5;
    playerRectangle.w = 10;
    playerRectangle.h = 10;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // int x = static_cast<int>(px);
    // int y = static_cast<int>(py);
    //SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderDrawRect(renderer, &playerRectangle);
    SDL_RenderFillRect(renderer, &playerRectangle);
}

void renderdBackground(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

}

int main()
{
    // Initilization
    bool running = true;
    SDL_Event event;

    //Window Init
    SDL_Init(SDL_INIT_EVERYTHING); // SDL INIT
    window = SDL_CreateWindow(  "coom", 
                                 SDL_WINDOWPOS_UNDEFINED, 
                                 SDL_WINDOWPOS_UNDEFINED,
                                 windowWidth,
                                 windowHeight,
                                 0); //I dont know if I like this formatting. Saw it in a tutorial.

    //Render Init
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_RenderClear(renderer);

    //plauer position Init
    px = 300.0; py = 200.0;
    int x = 300; int y = 200;

    while(running)
    {
        //If you want to limit the fps you can here
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) 
            {   
                running = false;
                break;
            }
        }
        renderdBackground(renderer);
        renderPlayer(renderer, px, py);
        // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        // SDL_RenderDrawPoint(renderer, x, y);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}



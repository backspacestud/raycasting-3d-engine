// for initializing and shutdown functions
#include <SDL2/SDL.h>

// for rendering images and graphics on screen
#include <SDL2/SDL_image.h>

// for using SDL_Delay() functions
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <vector>

#define windowWidth 600
#define windowHeight 480

float px, py; //player position


SDL_Event e;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
std::vector<SDL_FPoint> points;


void renderPlayer(SDL_Renderer* renderer, float px, float py)
{
    // SDL_FRect playerRectangle; //Rectangle function unused because its stupid and does not work :)
    // playerRectangle.x = px - 5;
    // playerRectangle.y = py + 5;
    // playerRectangle.w = 10;
    // playerRectangle.h = 10;
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // SDL_RenderDrawRectF(renderer, &playerRectangle);
    // SDL_RenderFillRectF(renderer, &playerRectangle);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawPointF(renderer, px, py);
}
void playerControls(SDL_Event& event , float& px, float& py) //Basic controlls down, Fix later (there is a delay also its just an if else stement lol)
{
    if (event.type == SDL_KEYDOWN) 
    {
        const Uint8* keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_W]) {
            py -= 1.0; // Move up

            if (keys[SDL_SCANCODE_A]) {
                px -= 1.0; // Move left
            } else if (keys[SDL_SCANCODE_D]) {
                px += 1.0; // Move right
            }
        } else if (keys[SDL_SCANCODE_S]) {
            py += 1.0; // Move down

            if (keys[SDL_SCANCODE_A]) {
                px -= 1.0; // Move left
            } else if (keys[SDL_SCANCODE_D]) {
                px += 1.0; // Move right
            }
        } else if (keys[SDL_SCANCODE_A]) {
            px -= 1.0; // Move left
        } else if (keys[SDL_SCANCODE_D]) {
            px += 1.0; // Move right
        }

    }
}

void renderBackground(SDL_Renderer* renderer)
{
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
            playerControls(event , px , py);
        }
        renderBackground(renderer);
        renderPlayer(renderer, px, py);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}



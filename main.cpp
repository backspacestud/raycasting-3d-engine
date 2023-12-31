// for initializing and shutdown functions
#include <SDL2/SDL.h>

// for rendering images and graphics on screen
#include <SDL2/SDL_image.h>

// for using SDL_Delay() functions
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <vector>
#include <math.h>

#define windowWidth 640
#define windowHeight 480
#define PI 3.1415926535

float px, py, pdx = 5, pdy = 0, pa = 0; //player position   pa = angle   dx/dy = delta


SDL_Event e;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
std::vector<SDL_FPoint> points;


void renderPlayer(SDL_Renderer* renderer, float px, float py)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawPointF(renderer, px, py);

    SDL_RenderDrawLineF(renderer, px, py, (px + pdx) , (py + pdy) );
}
void playerControls(SDL_Event& event , float& px, float& py) //Basic controlls down, Fix later (there is a delay also its just an if else stement lol)
{
    if (event.type == SDL_KEYDOWN) 
    {
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT]) { // ROTATION
            pa -= 0.1; // Rotate Left
            if (pa < 0) {
                pa = 2 * PI;
            }
            pdx = cos(pa) * 5;
            pdy = sin(pa) * 5;
            std::cout << "pdx = " << pdx << " and pdy = " << pdy << "and pa = " << pa << std::endl; 
        } else if (keys[SDL_SCANCODE_RIGHT]) {
            pa += 0.1; // Rotate Right
            if ( pa > (2 * PI) ) {
                pa = 0;
            }
            pdx = cos(pa) * 5;
            pdy = sin(pa) * 5;
            std::cout << "pdx = " << pdx << " and pdy = " << pdy << "and pa = " << pa << std::endl; 
        } else if (keys[SDL_SCANCODE_W]) { //DIRECTION
            py += pdy /2;
            px += pdx /2;
        } else if (keys[SDL_SCANCODE_S]) {
            py -= pdy /2;
            px -= pdx /2; 
        }

    }
}


void renderBackground(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

}

//temp map
int mapX= 8;
int mapY = 8;
int mapS = 32; //size
int map[] = 
{
    1,1,1,1,1,1,1,1,
    1,0,0,1,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,0,0,1,0,1,
    1,0,0,0,0,1,0,1,
    1,1,1,1,1,1,1,1,
};
SDL_Rect mapWallRect;


void renderMap2D(SDL_Renderer* renderer)
{
    int x, y, xo, yo;
    xo = 0;
    yo = 0;
    for (y=0; y<mapY; y++) 
    {
        for(x=0; x<mapX; x++)
        {
            if(map[y*mapY+x] == 1)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //black
            }
            xo = (x * mapS) +32; //xofset to keep on screenP
            yo = (y * mapS) -32; //yofset to keep on screen
            mapWallRect.x = xo - 32;
            mapWallRect.y = yo + 32;
            mapWallRect.w = mapS;
            mapWallRect.h = mapS;
            SDL_RenderDrawRect(renderer, &mapWallRect);
            SDL_RenderFillRect(renderer, &mapWallRect);
        }
    }
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

    //player position Init
    px = (mapX * mapS) / 2; py = (mapY * mapS) / 2;



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
        renderMap2D(renderer);
        renderPlayer(renderer, px, py);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}



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

float playerX, playerY, pdx = 5, pdy = 0, playerAngle = 0; //player position   playerAngle = angle   dx/dy = delta


SDL_Event e;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
std::vector<SDL_FPoint> points;
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



void renderPlayer(SDL_Renderer* renderer, float playerX, float playerY)
{   
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLineF(renderer, playerX, playerY, (playerX + pdx) , (playerY + pdy) );
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawPointF(renderer, playerY, playerY);

    
}
void playerControls(SDL_Event& event , float& playerX, float& playerY) //Basic controlls down, Fix later (there is a delay also its just an if else stement lol)
{
    if (event.type == SDL_KEYDOWN) 
    {
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_LEFT]) { // ROTATION
            playerAngle -= 0.1; // Rotate Left
            if (playerAngle < 0) {
                playerAngle = 2 * PI;
            }
            pdx = cos(playerAngle) * 5;
            pdy = sin(playerAngle) * 5;
            //std::cout << "pdx = " << pdx << " and pdy = " << pdy << "and playerAngle = " << playerAngle << std::endl; 
        } else if (keys[SDL_SCANCODE_RIGHT]) {
            playerAngle += 0.1; // Rotate Right
            if ( playerAngle > (2 * PI) ) {
                playerAngle = 0;
            }
            pdx = cos(playerAngle) * 5;
            pdy = sin(playerAngle) * 5;
            //std::cout << "pdx = " << pdx << " and pdy = " << pdy << "and playerAngle = " << playerAngle << std::endl; 
        } else if (keys[SDL_SCANCODE_W]) { //DIRECTION
            playerY += pdy /2;
            playerX += pdx /2;
        } else if (keys[SDL_SCANCODE_S]) {
            playerY -= pdy /2;
            playerX -= pdx /2; 
        }

    }
}


void renderBackground(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

}




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

// void renderRays3D(SDL_Renderer* renderer)
// {
//     float rayAngle, rayY, rayX, rayYOffset, rayXOffset;
//     int deapthOfField, mapRayX, mapRayY, mapRayP, r;
//     rayAngle = playerAngle;
//     for (r = 0; r < 1; r++)  // Changed loop condition to allow multiple iterations
//     {
//         // Check for Horizontal Lines
//         deapthOfField = 0;
//         float aTan = -1 / tan(rayAngle);
//         if (rayAngle > PI) // Ray is facing down
//         {
//             rayY = (((int)playerY >> 6) << 6) - 0.0001;
//             rayX = (playerY - rayY) * aTan + playerX;
//             rayYOffset = -mapS;
//             rayXOffset = -rayYOffset * aTan;
//         }
//         if (rayAngle < PI) // Ray is facing up
//         {
//             rayY = (((int)playerY >> 6) << 6) + mapS;
//             rayX = (playerY - rayY) * aTan + playerY;
//             rayYOffset = mapS;
//             rayXOffset = -rayYOffset * aTan;
//         }
//         if (rayAngle == 0 || rayAngle == PI)
//         {
//             rayX = playerX;
//             rayY = playerY;
//             deapthOfField = 8;
//         }
//         while (deapthOfField < 8)
//         {
//             mapRayX = (int)(rayX) >> 6;
//             mapRayY = (int)(rayY) >> 6;
//             mapRayP = mapRayY * mapS + mapRayX; // Corrected mapRayX
//             if (mapRayP < mapX * mapY && map[mapRayP] == 1) // hit wall
//             {
//                 deapthOfField = 8;
//             }
//             else
//             {
//                 rayX += rayXOffset;
//                 rayY += rayYOffset;
//                 deapthOfField += 1;
//             }
//         }

//         SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // blue
//         SDL_RenderDrawLineF(renderer, playerX, playerY, rayX, rayY);
//     }
// }

    


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
    playerX = (mapX * mapS) / 2; playerY = (mapY * mapS) / 2;



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
            playerControls(event , playerX , playerY);
        }
        renderBackground(renderer);
        renderMap2D(renderer);
        renderPlayer(renderer, playerX, playerY);


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}



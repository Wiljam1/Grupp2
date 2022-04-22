#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "player.h"

#define PUBLIC /* empty */
#define PRIVATE static
#define LENGTH 100

const int WIDTH = 800; 
const int HEIGHT = 450;

PRIVATE void updateMedia(Game newGame, SDL_Rect playerRect[]);
PRIVATE void createGameMedia(Game newGame);

struct game_type
{
    SDL_Window  *window;
    SDL_Surface *window_surface;

    //Renderer
    SDL_Renderer *renderer;

    //Images
    SDL_Texture *background;
    SDL_Texture *player_texture;
    
    SDL_Event    window_event;
}; 

//initializes game
PUBLIC Game createGame()
{
    Game newGame = malloc(sizeof(struct game_type));
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Failed to initialize SDL2: %s\n", SDL_GetError());
    }
    newGame->window= SDL_CreateWindow("Bowlerman 0.1", 
                                       SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 
                                       WIDTH, HEIGHT, 
                                       SDL_WINDOW_SHOWN);
    
    newGame->renderer = SDL_CreateRenderer(newGame->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    newGame->window_surface = SDL_GetWindowSurface(newGame->window);
    return newGame;
}

//handles processes, like keyboard-inputs etc
int checkEvents(Game newGame, PlayerMovement playerMoving)
{
    bool keep_window_open = true;
    while(SDL_PollEvent(&newGame->window_event) > 0)
    {
        SDL_Event event = newGame->window_event;
        
        switch(newGame->window_event.type)
        {
            case SDL_QUIT:
                keep_window_open = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    playerMoving->up = 1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    playerMoving->left = 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    playerMoving->down = 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    playerMoving->right = 1;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    playerMoving->up = 0;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    playerMoving->left = 0;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    playerMoving->down = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    playerMoving->right = 0;
                    break;
                }
                break;
        }
    }

    // determine velocity of player
    determinePlayerVelocity(playerMoving);

    // update (client-side) player positions
    updatePlayerClientPosition(playerMoving);

    // set the positions in the struct
    playerRect[0].x = (int) playerMoving->xPos;
    playerRect[0].y = (int ) playerMoving ->yPos;

    //check if within bounds
    //write in: collissiondetection.c

    return keep_window_open;
}

//initializes startvalues for game
PRIVATE void initGame(Game newGame)
{
    //loads in textures
    newGame->background = (SDL_Texture *) loadMedia(newGame, "grass00.bmp");
    SDL_FreeSurface(newGame->window_surface);
    newGame->player_texture = (SDL_Texture *) loadMedia(newGame, "pin2.png");
    SDL_FreeSurface(newGame->window_surface);


    Player player[3]; //declares 4 players.
    player[0] = initPlayer(50, 100);   //sets x and y coordinates
    initPlayerRect(&playerRect[0], player[0]); //inits playerRect[0] to position of player0
    
    //get and scale the dimensions of texture
    SDL_QueryTexture(newGame->player_texture, NULL, NULL, &playerRect[0].w, &playerRect[0].h);
    playerRect[0].w /=4;              //scales down width by 4
    playerRect[0].h /=4;              //scales down height by 4

    

}

//game loop
PUBLIC void gameUpdate(Game newGame) 
{
    initGame(newGame); //initializes startvalues. coordinates etc.
    
    PlayerMovement playerMoving;     //keep track of where player is moving
    resetPlayerMoving(playerMoving); //player is no longer moving
    

    //gameloop:
    bool keep_window_open = true;
    while(keep_window_open)
    {
        //Check for events
        keep_window_open = checkEvents(newGame, playerMoving);
        
        //handles events
        //handleEvents();

        //renders to screen
        updateMedia(newGame, playerRect); 

        SDL_Delay(10); //man behöver ta minus här för att räkna in hur lång tid spelet tar att exekvera
    }
}

//loads media into texture
PUBLIC SDL_Texture *loadMedia(Game newGame, char fileLocation[])   //loadmedia
{
    bool success = true;
    char fileLocationInResources[100]="resources/";
    strcat(fileLocationInResources, fileLocation);
    newGame->window_surface = IMG_Load(fileLocationInResources);
    if(newGame->window_surface == NULL)
    {
        printf("Failed to load surface! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    return SDL_CreateTextureFromSurface(newGame->renderer, newGame->window_surface);
}

//renders background and players etc.
PRIVATE void updateMedia(Game newGame, SDL_Rect playerRect[])
{
    SDL_RenderClear(newGame->renderer); //clear renderer

    //updates/renders background
    SDL_RenderCopy(newGame->renderer, newGame->background, NULL, NULL);

    //renders media (like players etc)
    SDL_RenderCopy(newGame->renderer, newGame->player_texture, NULL, &playerRect[0]);

    SDL_RenderPresent(newGame->renderer); //present renderer
}

PUBLIC void destroyGame(Game theGame)
{
    SDL_DestroyTexture(theGame->background);
    SDL_DestroyTexture(theGame->player_texture);
    SDL_DestroyRenderer(theGame->renderer);
    SDL_DestroyWindow(theGame->window);
    SDL_Quit();
}
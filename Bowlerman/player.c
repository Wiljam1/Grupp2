#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"
#include "game.h"
#include "collissionDetection.h"
PUBLIC Player initPlayer(float xPos, float yPos)
{
    malloc(sizeof(struct playerController));

    Player p;

    p.up = 0;
    p.down = 0;
    p.right = 0;
    p.left = 0;
    p.xVel = 0;
    p.yVel = 0;
    p.xPos = p.xPosOld = xPos;
    p.yPos = p.yPosOld = yPos;
    p.speed = 3;
    p.height = 80;
    p.width = 50;

    return p;
}

PUBLIC void LoadPlayerTextures(Game theGame, int ID, char sourceText[10])
{
    if (strcmp(sourceText, "red"))
    {
        theGame->player_texture[0][0] = (SDL_Texture *)loadTextures(theGame, "/resources/redman/redmanleft.png");
        theGame->player_texture[0][1] = (SDL_Texture *)loadTextures(theGame, "/resources/redman/redmandown.png");
        theGame->player_texture[0][2] = (SDL_Texture *)loadTextures(theGame, "/resources/redman/redmanup.png");
    }
    else if (strcmp(sourceText, "blue"))
    {
        theGame->player_texture[1][0] = (SDL_Texture *)loadTextures(theGame, "/resources/blueman/bluemanleft.png");
        theGame->player_texture[1][1] = (SDL_Texture *)loadTextures(theGame, "/resources/blueman/bluemandown.png");
        theGame->player_texture[1][2] = (SDL_Texture *)loadTextures(theGame, "/resources/blueman/bluemanup.png");
    }
    else if (strcmp(sourceText, "purple"))
    {
        theGame->player_texture[2][0] = (SDL_Texture *)loadTextures(theGame, "/resources/purpleman/purplemanleft.png");
        theGame->player_texture[2][1] = (SDL_Texture *)loadTextures(theGame, "/resources/purpleman/purplemandown.png");
        theGame->player_texture[2][2] = (SDL_Texture *)loadTextures(theGame, "/resources/purpleman/purplemanup.png");
    }
    else if (strcmp(sourceText, "yellow"))
    {
        theGame->player_texture[3][0] = (SDL_Texture *)loadTextures(theGame, "/resources/purpleman/purplemanleft.png");
        theGame->player_texture[3][1] = (SDL_Texture *)loadTextures(theGame, "/resources/purpleman/purplemandown.png");
        theGame->player_texture[3][2] = (SDL_Texture *)loadTextures(theGame, "/resources/purpleman/purplemanup.png");
    }
    SDL_FreeSurface(theGame->window_surface);
}

PUBLIC int getPlayerHeight(Player p)
{
    return p.height;
}
PUBLIC int getPlayerWidth(Player p)
{
    return p.width;
}
PUBLIC float getPlayerXPosition(Player p)
{
    return p.xPos;
}
PUBLIC float getPlayerYPosition(Player p)
{
    return p.yPos;
}

//REplaced by different movement-implementation

// PUBLIC void determinePlayerVelocity(Player p)
// {
//     p->xVel=0;
//     p->yVel=0;
//     if(p->up && !p->down) p->yVel = -p->speed;
//     if(p->down && !p->up) p->yVel = p->speed;
//     if(p->left && !p->right) p->xVel = -p->speed;
//     if(p->right && !p->left) p->xVel = p->speed;
// }
// PUBLIC void updatePlayerClientPosition(Player p)
// {
//     p->xPos += p->xVel;
//     p->yPos += p->yVel;
// }

// PUBLIC void destroyPlayer(Player player)
// {
    
// }

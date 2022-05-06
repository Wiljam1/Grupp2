#ifndef bomb_h
#define bomb_h
#include <SDL2/SDL.h>
#include "player.h"
#include "game.h"

#define PLAYERAMOUNT 4

struct bowling_ball typedef Bowlingball;

struct bowling_ball
{
    //int id;   
    //float yVel, xVel, xPos, yPos;
    //float xPosOld;
    //float yPosOld;
    SDL_Rect position;
    //int height;
    //int width;
    int timervalue;
    int speed;
    int timerinit;
    int explosioninit;
    int placedBombRestriction;
    int powerUpExplosion ;

    //int frame;
};

int initbowlingballtimer(int startTime, int timeAmount, int playerID);

int correctBowlingBallPos(int i);

//int checkbowlingballtimer();

SDL_Rect bowlingballAnimation[18];


Bowlingball initBomb(int playerID);
void loadBomb();

//SDL_Rect setBowlingBallPosition(Game theGame, Player player);

//Bowlingball createBowlingBall();

//int getBowlingBallPositionX(Bowlingball ball);
//int getBowlingBallPositionY(Bowlingball ball);
//int getBowlingBallWidth();
//int getBowlingBallHeight();
//int getBowlingBallFrame(Bowlingball ball);





#endif
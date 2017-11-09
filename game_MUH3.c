/*
 * tag_game.c
 *
 *  Created on: May 05, 2017
 *      Author: Heimlich
 */
////////////////////////////MMmmbbbb
#include "system.h"
#include "random_int.h"
#include "strings.h"
#include "game.h"
#include "timing.h"
#include "task.h"
#include "terminal.h"
#include "random_int.h"
#ifdef USE_MODULE_GAME_CONTROLLER
#include "game_controller_host.h"
#include "game_controller.h"
#endif

#define MAP_WIDTH 52
#define MAP_HEIGHT 22

/// game structure
struct tag_game_t {
    char x; // x coordinate of player
    char y; // y coordinate of player
    char c; // character of player
    int score; // time survived
    uint8_t id; ///< ID of game=
};

static struct tag_game_t game;

static void Callback(int argc, char * argv[]);
static void Receiver(char c);

static void Play(void);
static void Help(void);

static void DetectCollision(void);
static void GameOver(void);
static void MoveRight(void);
static void MoveLeft(void);
static void MoveUp(void);
static void MoveDown(void);

void tag_Init(void) {
    // Register the module with the game system and give it the name "MUH3"
    game.id = Game_Register("tag", "simple tag match", Play, Help);
    // Register a callback with the game system.
    // this is only needed if your game supports more than "play", "help" and "highscores"
    Game_RegisterCallback(game.id, Callback);
}

void Help(void) { 
    Game_Printf("Use WASD to move up, left, down, and right\r\n"
            "Avoid the ''It'' AI!\r\n");
}

void Callback(int argc, char * argv[]) {
    // "play" and "help" are called automatically so just process "reset" here
    if(argc == 0) Game_Log(game.id, "too few args");
    if(strcasecmp(argv[0],"reset") == 0) {
        // reset scores
        game.score = 0;
        Game_Log(game.id, "Scores reset");
    }else Game_Log(game.id, "command not supported");
}

void Play(void) {

    // clear the screen
    Game_ClearScreen();

    // initialize game variables
    game.Ex = 0;
    game.Ey = 0;
    game.Ec = 219;
    game.Px = (MAP_WIDTH / 2) + 1;
    game.Py = (MAP_HEIGHT / 2) + 1;
    game.Pc = 220;
    game.score = 0;

    // draw a box around our map
    Game_DrawRect(0, 0, MAP_WIDTH, MAP_HEIGHT);

    //Set receiver
    Game_RegisterPlayer1Receiver(Receiver);

    // hide cursor
    Game_HideCursor();
}

void Receiver(char c) {
    switch (c) {
        case 'a':
        case 'A':
            MoveLeft();
            break;
        case 'd':
        case 'D':
            MoveRight();
            break;
        case 'w':
        case 'W':
            MoveUp();
            break;
        case 's':
        case 'S':
            MoveDown();
            break;
        default:
            break;
    }
}

void MoveRight(void) {
    while (Game_IsTransmitting()) DelayMs(2);
    // make sure we can move right
    if (game.Px < MAP_WIDTH - 1) {
        //Remove previous space character
        Game_CharXY(' ', game.Px, game.Py);
        game.Px++;
        //Draw current space character
        Game_CharXY(game.Pc, game.Px, game.Py);
    }
}

void MoveLeft(void) {
    while (Game_IsTransmitting()) DelayMs(2);
    // make sure we can move right
    if (game.Px > 1) {
        //Remove previous space character
        Game_CharXY(' ', game.Px, game.Py);
        game.Px--;
        //Draw current space character
        Game_CharXY(game.Pc, game.Px, game.Py);
    }
}

void MoveUp(void) {
    while (Game_IsTransmitting()) DelayMs(2);
    // make sure we can move right
    if (game.Py > 1)
    {
        //Remove previous space character
        Game_CharXY(' ', game.Px, game.Py);
        game.Py--;
        //Draw current space character
        Game_CharXY(game.Pc, game.Px, game.Py);
    }
}

void MoveDown(void) {
    while (Game_IsTransmitting()) DelayMs(2);
    // make sure we can move right
    if (game.Py < MAP_HEIGHT -1) {
        //Remove previous space character
        Game_CharXY(' ', game.Px, game.Py);
        game.Py++;
        //Draw current space character
        Game_CharXY(game.Pc, game.Px, game.Py);
    }
    DetectCollision();
}

void MoveEnemy(void)
{
    while (Game_IsTransmitting()) DelayMs(2);
    xDiff = game.Ex-game.Px;
    yDiff = game.Ey-game.Py;

    //Remove previous space character
    Game_CharXY(' ', game.Ex, game.Ey);

    // Determine along which axis the enemy is further to the player
    // -- Defaults to Y axis if equal
    if(abs(xDiff) > abs(yDiff))
    {
        // Determine whether to move left or right
        if(xDiff > 0)
            game.Ex--; // Move enemy left
        else
            game.Ex++; // Move enemy right
    }
    else
    {
        // Determine whether to move left or right
        if(yDiff > 0)
            game.Ey++; // Move enemy up
        else
            game.Ey--; // Move enemy down
    }

    //Draw current space character
    Game_CharXY(game.Ec, game.Ex, game.Ey);
    DetectCollision();
}

void DetectCollision(void)
{
    if(game.Ex == game.Px && game.Ey == game.Py)
        GameOver();
}

void GameOver(void) {
    // play loss sound
    Game_Bell();

    // Calculate time survived
    int timeMinute = game.score/60;
    int timeSecond = game.score - (timeMinute*60);

    // end cursor enemy move task


    // set cursor below bottom of map
    Game_CharXY('\r', 0, MAP_HEIGHT + 1);

    // show time survived
    Game_Printf("Game Over! Time Survived: %d minutes, %d seconds", timeMinute, timeSecond);
    // unregister the receiver used to run the game
    Game_UnregisterPlayer1Receiver(Receiver);
    // show cursor (it was hidden at the beginning
    Game_ShowCursor();
    Game_GameOver();
}

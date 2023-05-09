// GameCreation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "GameWorld.h"
#include "SDL_ttf.h"
#include "LogTime.h"
//SDL_Window* globWindow = 0;
//SDL_Renderer* globRender = 0;
bool gRun = false; //global variables that should work in all files
GameWorld* gGame = 0;
using namespace std;
int main(int argc, char* args[])
{
    LogTime::clear();
    srand(time(NULL));
    char logMessage[32];
    LogTime::getTime(logMessage, 32);
    if (SDL_Init(SDL_INIT_EVERYTHING >= 0)) return 1; //makes sure SDL is initialised
    IMG_Init(SDL_INIT_EVERYTHING); //makes SDL_Image initialised
    if (SDL_Init(SDL_INIT_AUDIO) == -1) SDL_Quit();
    if (TTF_Init() == 1) SDL_Quit();
    gGame = new GameWorld(); //create a dynamic gameworld object
    LogTime::open();
    gGame->Init("Jonathan Byrne-ID:BYR19702034-CGPM2015M Games Programming. Frog Collection", 100, 100, 800, 600, SDL_WINDOW_RESIZABLE); //assign the parameters to create the SDL_Window in the game world
    gGame->Splash();
    SDL_Delay(3000);
    SDL_Log("[%s] [MAIN GAME HAS LOADED] [%i]", logMessage, SDL_GetTicks());
    LogTime::write("MAIN GAME HAS LOADED", SDL_GetTicks(), logMessage);
    while (gGame->getRunning()) //while running the game
    {
        gGame->Input();
        gGame->Update();
        gGame->Render();
    }
    gGame->End();
    SDL_Delay(3000);
    SDL_Log("[%s] [GAME HAS EXITED] [%i]", logMessage, SDL_GetTicks());
    LogTime::write("GAME HAS EXITED", SDL_GetTicks(), logMessage);
    gGame->Clean(); //deletes the window and renderer
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include "GameOverMenuController.h"

#include "Inputs/InputsMethods.h"
#include "../../App.h"
#include "Gameplay/GamePlayScene/Game.h"
#include "Gameplay/GamePlayScene/GameOverMenu.h"

void run::GameOverMenuController::Init()
{
    keybinds.insert({"restart", sr::Keyboard::R});
    keybinds.insert({"quit", sr::Keyboard::ESCAPE});
}

void run::GameOverMenuController::CheckInputs(float32 deltatime)
{
    // Get inputs 
    if (sr::GetKeyDown(keybinds["restart"]))
    {
        //Restart Game
        run::Game* game = APP.GetScene<run::Game>();
        game->Restart();
        game->Resume();
        
        // Stop GameOverMenu
        run::GameOverMenu* gameover = APP.GetScene<run::GameOverMenu>();
        gameover->Pause();
        gameover->Hide();
    }
    if (sr::GetKeyDown(keybinds["quit"]))
    {
        // Quit the game
        exit(0);
    }
}
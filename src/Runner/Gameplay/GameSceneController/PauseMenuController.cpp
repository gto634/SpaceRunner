#include "PauseMenuController.h"

#include "Inputs/InputsMethods.h"
#include "../../App.h"
#include "Gameplay/GamePlayScene/Game.h"
#include "Gameplay/GamePlayScene/PauseMenu.h"

void run::PauseMenuController::Init()
{
    keybinds.insert({"resume", sr::Keyboard::ENTER});
    keybinds.insert({"restart", sr::Keyboard::R});
    keybinds.insert({"quit", sr::Keyboard::ESCAPE});
}

void run::PauseMenuController::CheckInputs(float32 deltatime)
{
    // Get inputs 
    if (sr::GetKeyDown(keybinds["resume"]))
    {
        run::PauseMenu* pauseMenu = APP.GetScene<run::PauseMenu>();
        pauseMenu->Pause();
        pauseMenu->Hide();
        APP.GetScene<run::Game>()->Resume();
    }
    if (sr::GetKeyDown(keybinds["restart"]))
    {
        //Restart Game
        run::Game* game = APP.GetScene<run::Game>();
        game->Restart();
        game->Resume();
        
        // Stop GameOverMenu
        run::PauseMenu* pause = APP.GetScene<run::PauseMenu>();
        pause->Pause();
        pause->Hide();
    }
    if (sr::GetKeyDown(keybinds["quit"]))
    {
        // Way to quit the game
        exit(0);
    }
}
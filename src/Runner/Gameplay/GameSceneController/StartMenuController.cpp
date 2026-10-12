#include "StartMenuController.h"

#include "Inputs/InputsMethods.h"
#include "../../App.h"
#include "Gameplay/GamePlayScene/Game.h"
#include "Gameplay/GamePlayScene/StartMenu.h"

void run::StartMenuController::Init()
{
    keybinds.insert({"start", sr::Keyboard::ENTER});
    keybinds.insert({"quit", sr::Keyboard::ESCAPE});
}

void run::StartMenuController::CheckInputs(float32 deltatime)
{
    // Get inputs 
    if (sr::GetKeyDown(keybinds["start"]))
    {
        run::StartMenu* startMenu = APP.GetScene<run::StartMenu>();
        startMenu->Pause();
        startMenu->Hide();
        APP.GetScene<run::Game>()->Resume();
    }
    if (sr::GetKeyDown(keybinds["quit"]))
    {
        // Way to quit the game
        exit(0);
    }
}
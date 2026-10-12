#ifndef RUNNER_CONTROLLER_H
#define RUNNER_CONTROLLER_H

#include <GCE/Core/define.h>
#include "Inputs/InputsEnums.h"

namespace run
{
    class Controller
    {
    public :
       Controller() = default;
        virtual void CheckInputs(float32 deltatime) = 0;

        virtual ~Controller() = default;
    protected :
        UnorderedMap<String, sr::Keyboard::Key> keybinds;
    };
}

#endif
#pragma once

#include "CommonLib.h"
#include <Control.hpp>
#include <TextureProgress.hpp>
#include <string>

#include "Counter.h"


class InterfaceManager :
    public Control
{
    //godot structure
    GODOT_CLASS(InterfaceManager, Control);

public:
    static void _register_methods();
    void _init();

    void _ready();

    void SetHP(int current, int max);
    void SetDMG(int damage);
    void SetScore(int score);

private:
    Counter* HP;
    TextureProgress* HPBar;
    Counter* DMG;
    Counter* Score;
};


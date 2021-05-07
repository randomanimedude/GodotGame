#pragma once

#include "CommonLib.h"
#include <TextureProgress.hpp>
#include <Node2D.hpp>

class EnemyHealthBar :
    public TextureProgress
{
    //godot structure
    GODOT_CLASS(EnemyHealthBar, TextureProgress);

public:
    static void _register_methods();
    void _init();

    void _ready();
    void TurnAround();
    void SetProgress(int current, int max);
};


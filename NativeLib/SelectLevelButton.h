#pragma once
#include "CommonLib.h"
#include "DataLoader.h"
#include "LevelManager.h"
#include <Button.hpp>

class SelectLevelButton :
    public Button
{
    GODOT_CLASS(SelectLevelButton, Button);

    int level_index = 0;
    bool secret_level = false;


public:
    static void _register_methods();
    void _init();

    void _ready();
    void _on_Button_mouse_entered();
    void _on_Button_pressed();


private:
    DataLoader* dataLoader;
    LevelManager* levelManager;
};


#pragma once

#include "CommonLib.h"
#include <NinePatchRect.hpp>
#include <Label.hpp>

class Counter :
    public NinePatchRect
{
    //godot structure
    GODOT_CLASS(Counter, NinePatchRect);

public:
    static void _register_methods();
    void _init();

    void _ready();

    void SetValue(String str);

private:
    Label* value;
};


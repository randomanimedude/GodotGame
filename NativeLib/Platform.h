#pragma once

#include "CommonLib.h"

#include <KinematicBody2D.hpp>


class Platform :
    public KinematicBody2D
{
    GODOT_CLASS(Platform, KinematicBody2D);

public:
    static void _register_methods();
    void _init();

    void _ready();

private:
    Node2D* start;
    Node2D* end;


};


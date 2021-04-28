#pragma once

#include "CommonLib.h"

#include <KinematicBody2D.hpp>


class Platform :
    public KinematicBody2D
{
    GODOT_CLASS(Platform, KinematicBody2D);

    /*int max_speed_x = 100;
    int max_speed_y = 100;
    int acceleration_x = 10;
    int acceleration_y = 10;*/
    float acceleration = 1;
    float max_speed = 1;

public:
    static void _register_methods();
    void _init();

    void _ready();
    void _physics_process(float delta);
    void Move();
    void GoBack();

private:
    Vector2 currentPosition;
    Vector2 start;
    Vector2 end;
    Vector2 motion;
    Vector2 accelerationVector;
    Vector2 maxSpeedVector;
    bool endIsBelow;
    bool endIsOnRigh;


    bool toEnd = true;
};


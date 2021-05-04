#pragma once

#include "CommonLib.h"
#include "Player.h"
#include <Area2D.hpp>

class DamagingArea :
    public Area2D
{
    GODOT_CLASS(DamagingArea, Area2D);

    int damage = 20;
    bool impact = false;

private:
    Player* player;
    bool playerInside = false;

public:
    static void _register_methods();
    void _init();

    void _ready();
    void _physics_process(float delta);
    void _on_body_entered(PhysicsBody2D* body);
    void _on_body_exited(PhysicsBody2D* body);

};


#pragma once

#include "CommonLib.h"
#include "Player.h"
#include <KinematicBody2D.hpp>
#include <Area2D.hpp>

class Rashid :
    public KinematicBody2D
{
    GODOT_CLASS(Rashid, KinematicBody2D);
    int damage = 10;
    int health = 30;
    int score_reward = 10;

private:
    Area2D* detector;
    Area2D* damageDealer;
    AnimationPlayer* animator;
    bool triggered = false;

public:
    static void _register_methods();
    void _init();

    void _ready();
    void _physics_process(float delta);
    void _on_body_entered_detector(PhysicsBody2D* body);
    void _on_body_entered_damageDealer(PhysicsBody2D* body);


    void DealDamage(int dmg);

private:
    void Die();
};


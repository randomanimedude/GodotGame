#pragma once

#include "CommonLib.h"
#include <KinematicBody2D.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <AnimationPlayer.hpp>
#include <cstdlib>

class Boss :
    public KinematicBody2D
{
    GODOT_CLASS(Boss, KinematicBody2D);

    int HP = 200;
    int damage = 15;
    int score_reward = 1;

public:
    static void _register_methods();
    void _init();

    void _ready();
    void SpawnEnemy(int index);
    void DealDamage(int damage);

private:
    void Spawn(Vector2 position);

    Vector2 spawnPosition1;
    Vector2 spawnPosition2;
    Vector2 spawnPosition3;

    AnimationPlayer* animator;

    Ref<PackedScene> robat;
    Ref<PackedScene> rashid;
};


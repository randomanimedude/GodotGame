#pragma once

#include "CommonLib.h"
#include "Rashid.h"
#include "Robat.h"
#include "EnemyHealthBar.h"
#include <KinematicBody2D.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <AnimationPlayer.hpp>
#include <RayCast2D.hpp>
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
    void _physics_process(float delta);
    void SpawnEnemy(int index);
    void DealDamage(int damage);
    void OpenWindow();
    void RandomAtack();
    void DamagePlayer();
    void _on_body_entered(PhysicsBody2D* body);

private:
    void Spawn(Vector2 position);
    void Die();

    int maxHP;
    float waitTime = 0;
    bool active = false;

    Vector2 spawnPosition1;
    Vector2 spawnPosition2;
    Vector2 spawnPosition3;
    Vector2 robatScale = Vector2(3.557, 5.677);
    Vector2 rashidScale = Vector2(5, 7);

    AnimationPlayer* animator;
    EnemyHealthBar* healthBar;
    Area2D* damagingArea;
    RayCast2D* playerDetector;
    RayCast2D* minionDetector1;
    RayCast2D* minionDetector2;
    RayCast2D* minionDetector3;

    Ref<PackedScene> robat;
    Ref<PackedScene> rashid;
};


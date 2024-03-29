#pragma once

#include "CommonLib.h"
#include "BulletManager.h"
#include "InterfaceManager.h"

#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <AnimationPlayer.hpp>
#include <SceneTree.hpp>
#include <AudioStreamPlayer.hpp>


class Player : public KinematicBody2D
{
	//godot structure
	GODOT_CLASS(Player, KinematicBody2D);

	//exposed vars
	int max_HP = 100;
	int starting_damage = 10;
	int max_speed = 800;
	int gravity = 70;
	int max_fall_speed = 1200;
	int jump_force = 1600;
	int acceleration = 50;
	float zanos = 0.2f;
	int hit_impact_x = 300;
	int hit_impact_y = -300;
	float damage_cooldown = 1.0f;

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _process(float delta);
	void _physics_process(float delta);


	//gayplay vars
public:
	const Vector2 UP = Vector2(0, -1);

	bool facing_right = true;

private:
	static inline Player* instance;

	Vector2 motion;
	AnimationPlayer* animator;
	BulletManager* bulletManager;
	Input* inp;
	Node2D* bulletSpawnPositionRight;
	Node2D* bulletSpawnPositionLeft;
	InterfaceManager* interfaceManager;

	float damagedFor = 0;
	bool damaged = false;
	bool jumping = true;
	int  impact = 0;
	bool dead = false;
	int HP;
	int damage;
	int score = 0;

	//gayplay methods
public:
	void DealDamage(Vector2 hitPoint, int dmg, bool commitImpact);
	void ShootRight();
	void ShootLeft();
	void AddScore(int num);
	int GetScore();
	void IncreaseDamage(int bonus);
	void Heal(int hp);
	void IncreaseHP(int hp, bool heal);
	void StopGame();

	static Player* GetInstance();

private:
	void UpdateMotionFromInput();
	void Die();

};


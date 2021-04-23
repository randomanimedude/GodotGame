#pragma once

#include "CommonLib.h"
#include "BulletManager.h"

#include <KinematicBody2D.hpp>
#include <AnimationPlayer.hpp>
#include <KinematicCollision2D.hpp>
#include <RayCast2D.hpp>

class Robat : public KinematicBody2D
{
	//godot structure
	GODOT_CLASS(Robat, KinematicBody2D);

	//exposed vars
	int max_speed = 800;
	int gravity = 70;
	int max_fall_speed = 1200;
	int acceleration = 50;
	float zanos = 0.2f;

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _process(float delta);
	void _physics_process(float delta);


	//gayplay vars
public:
	const Vector2 UP = Vector2(0, -1);
	Vector2 scale;

private:
	Vector2 motion;
	Node2D* bulletSpawnPositionLeft;
	Node2D* bulletSpawnPositionRight;
	Node* nodeFinder;
	AnimationPlayer* animator;
	BulletManager* bulletManager;
	RayCast2D* floorDetector;
	RayCast2D* playerDetector;
	bool facing_right = false;
	bool isShooting = false;

	//gayplay methods
public:
	void Destroy();
	void ShootLeft();
	void ShootRight();

private:
	void ShootAtSight();
	void Move();
	void TurnAroundIfNeeded();
};


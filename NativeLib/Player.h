#pragma once

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <AnimationPlayer.hpp>

#include "BulletManager.h"

using namespace godot;

class Player : public KinematicBody2D
{
	//godot structure
	GODOT_CLASS(Player, KinematicBody2D);

	//exposed vars
	int max_speed = 300;
	int gravity = 20;
	int max_fall_speed = 400;
	int jump_force = 500;
	int acceleration = 20;
	float zanos = 0.2;

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
	Vector2 motion;
	Vector2 oldMotion;
	Node* nodeFinder;
	AnimationPlayer* animator;
	BulletManager* bulletManager;
	Input* inp;

	bool onFloor = false;


	//gayplay methods
public:
	void UpdateMotionFromInput();

private:
	int clamp(int x, int min, int max);

};


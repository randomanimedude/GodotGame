#pragma once

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <AnimationPlayer.hpp>
#include <KinematicCollision2D.hpp>

#include "CommonLib.h"

using namespace godot;

class Robat : public KinematicBody2D
{
	//godot structure
	GODOT_CLASS(Robat, KinematicBody2D);

	//exposed vars
	int max_speed = 800;
	int gravity = 70;
	int max_fall_speed = 1200;
	int acceleration = 50;

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

	bool facing_right = true;

private:
	Vector2 motion;
	Node* nodeFinder;
	AnimationPlayer* animator;


	//gayplay methods
public:
	void Destroy();
	void MoveFromWallToWall();
};


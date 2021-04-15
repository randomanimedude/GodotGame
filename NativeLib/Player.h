#pragma once

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>

using namespace godot;

class Player : public KinematicBody2D
{
	//godot structure
private:
	GODOT_CLASS(Player, KinematicBody2D);

public:
	static void _register_methods();
	void _init();
	void _physics_process(float delta);

	Player();
	~Player();


	//gayplay vars
public:
	const Vector2 UP = Vector2(0, -1);

	const int MAXSPEED = 300;
	const int GRAVITY = 20;
	const int MAXFALLSPEED = 400;
	const int JUMPFORCE = 800;
	const int ACCELERATION = 20;

private:
	Vector2 motion;


	//gayplay methods
public:
	void UpdateMotionFromInput();

private:
	int clamp(int x, int min, int max);

};


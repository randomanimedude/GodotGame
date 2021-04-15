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
	void _process(float delta);

	Player();
	~Player();


	//gayplay vars
public:
	const int speed = 300;

private:
	Vector2 motion;


	//gayplay methods
public:
	void UpdateMotionFromInput();

private:


};


#pragma once

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>

using namespace godot;

class Bullet : public KinematicBody2D
{
	//godot structure
	GODOT_CLASS(Bullet, KinematicBody2D);

	//exposed vars
	int bullet_speed = 1;

public:
	static void _register_methods();
	void _init();
	void _ready();

	void _physics_process(float delta);

	//gayplay vars
public:

private:
	Vector2 motion;

	

	//gayplay methods
public:
	void UpdatePosition(Vector2 position, bool facingRight);

private:
	void UpdateMotion();
	
	
};


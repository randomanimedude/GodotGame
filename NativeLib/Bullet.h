#pragma once

#include "CommonLib.h"

#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <CollisionShape2D.hpp>

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
	Node2D* parent;
	CollisionShape2D* collision;
	Vector2 motion;
	bool enabled;
	bool byPlayer;

	//gayplay methods
public:
	void UpdatePosition(Vector2 position, bool facingRight, bool byPlayer);
	void Disable();
	void Enable();
	bool IsEnabled();


private:
	void DestroyIfEnemy(Ref<KinematicCollision2D> collision);
	void UpdateMotion();
	
};


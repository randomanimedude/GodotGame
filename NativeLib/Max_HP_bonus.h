#pragma once

#include "CommonLib.h"
#include "Player.h"
#include <Area2D.hpp>
#include <AnimationPlayer.hpp>

class Max_HP_bonus :
	public Area2D
{
	GODOT_CLASS(Max_HP_bonus, Area2D);

	int health_bonus = 15;
	bool full_heal = true;

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _on_body_entered(PhysicsBody2D* body);
};
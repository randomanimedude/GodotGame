#pragma once

#include "CommonLib.h"
#include "Player.h"
#include <Area2D.hpp>
#include <AnimationPlayer.hpp>

class Heal :
	public Area2D
{
	GODOT_CLASS(Heal, Area2D);

	int heal = 10;

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _on_body_entered(PhysicsBody2D* body);
};
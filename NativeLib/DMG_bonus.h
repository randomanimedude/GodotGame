#pragma once

#include "CommonLib.h"
#include "Player.h"
#include <Area2D.hpp>
#include <AnimationPlayer.hpp>

class DMG_bonus:
	public Area2D
{
	GODOT_CLASS(DMG_bonus, Area2D);

	int damage_bonus = 5;

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _on_body_entered(PhysicsBody2D* body);
};


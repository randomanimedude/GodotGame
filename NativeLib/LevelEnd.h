#pragma once

#include "CommonLib.h"
#include <Area2D.hpp>

#include "Player.h"
#include "LevelManager.h"

class LevelEnd :
    public Area2D
{
	GODOT_CLASS(LevelEnd, Area2D);

	int this_level_id = 0;
	int next_level_id = 1;

public:
	static void _register_methods();
	void _init();

	void _ready();
	void _on_body_entered(PhysicsBody2D* body);

private:
	LevelManager* levelManager;
};


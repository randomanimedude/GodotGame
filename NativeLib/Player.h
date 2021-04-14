#pragma once
#include "Common.h"
#include <KinematicBody2D.hpp>

class Player : public KinematicBody2D
{
	GODOT_CLASS(Player, KinematicBody2D);

public:
	static void _register_methods();
	void _init();
};


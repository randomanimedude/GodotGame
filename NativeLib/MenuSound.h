#pragma once

#include "CommonLib.h"

#include <AudioStreamPlayer.hpp>

class MenuSound : 
    public AudioStreamPlayer
{
	GODOT_CLASS(MenuSound, AudioStreamPlayer);

public:
	static void _register_methods();
	void _init();
	void _ready();

};


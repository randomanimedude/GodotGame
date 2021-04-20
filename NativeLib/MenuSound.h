#pragma once
#include <Godot.hpp>
#include <AudioStreamPlayer.hpp>

using namespace godot;

class MenuSound : 
    public AudioStreamPlayer
{
	GODOT_CLASS(MenuSound, AudioStreamPlayer);

public:
	static void _register_methods();
	void _init();
	void _ready();

};


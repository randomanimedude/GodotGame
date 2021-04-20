#pragma once
#include <Godot.hpp>
#include <AudioStreamPlayer2D.hpp>

using namespace godot;

class MenuSound : 
    public AudioStreamPlayer2D
{
	GODOT_CLASS(MenuSound, AudioStreamPlayer2D);

public:
	static void _register_methods();
	void _init();
	void _ready();

};


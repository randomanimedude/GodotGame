#pragma once

#include "CommonLib.h"
#include "DataLoader.h"

#include <Button.hpp>
#include <SceneTree.hpp>
#include <Node2D.hpp>

class Menu_buttons :
    public Button
{
    GODOT_CLASS(Menu_buttons, Button);

	String reference_path = "";
	bool start_focused = false;
	bool load_scene = true;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void  _on_Button_mouse_entered();
	void _on_Button_Pressed();
};


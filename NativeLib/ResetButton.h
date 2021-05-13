#pragma once
#include "CommonLib.h"
#include <Button.hpp>
#include <SceneTree.hpp>

class ResetButton :
    public Button
{
	GODOT_CLASS(ResetButton, Button);

	String reference_path = "";
	bool start_focused = false;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void  _on_Button_mouse_entered();
	void _on_Button_Pressed();
};


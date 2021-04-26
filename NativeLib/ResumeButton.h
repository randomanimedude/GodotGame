#pragma once

#include "CommonLib.h"
#include "Button.hpp"
#include "PauseScreen.h"

class ResumeButton :
    public Button
{
	GODOT_CLASS(ResumeButton, Button);

public:
	static void _register_methods();
	void _init();


	void _ready();
	void _on_Button_mouse_entered();
	void _on_Button_Pressed();
};


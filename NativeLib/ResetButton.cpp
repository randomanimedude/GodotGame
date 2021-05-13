#include "ResetButton.h"

void ResetButton::_register_methods()
{
	register_method("_ready", &ResetButton::_ready);
	register_method("_on_Button_mouse_entered", &ResetButton::_on_Button_mouse_entered);
	register_method("_on_Button_Pressed", &ResetButton::_on_Button_Pressed);
}

void ResetButton::_init()
{
}

void ResetButton::_ready()
{
	connect("mouse_entered", this, "_on_Button_mouse_entered");
	connect("pressed", this, "_on_Button_Pressed");
}

void ResetButton::_on_Button_mouse_entered()
{
	grab_focus();
}

void ResetButton::_on_Button_Pressed()
{
	get_tree()->reload_current_scene();
}

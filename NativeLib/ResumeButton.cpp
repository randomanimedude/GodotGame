#include "ResumeButton.h"


void ResumeButton::_register_methods()
{
	register_method("_on_Button_mouse_entered", &ResumeButton::_on_Button_mouse_entered);
	register_method("_on_Button_Pressed", &ResumeButton::_on_Button_Pressed);
	register_method("_ready", &ResumeButton::_ready);
}

void ResumeButton::_init()
{
}


void ResumeButton::_ready()
{ 
	grab_focus();
	connect("mouse_entered", this, "_on_Button_mouse_entered");
	connect("pressed", this, "_on_Button_Pressed");
}
void ResumeButton::_on_Button_mouse_entered()
{
	grab_focus();
}

void ResumeButton::_on_Button_Pressed()
{
	PauseScreen::getInstance()->Pause();
}
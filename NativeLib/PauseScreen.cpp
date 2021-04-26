#include "PauseScreen.h"

void PauseScreen::_register_methods()
{
	register_method("_input", &PauseScreen::_input);
}

void PauseScreen::_init()
{
	instance = this;
}

void PauseScreen::_input(InputEvent* e)
{
	if (e->is_action_pressed("pause"))
		Pause();
}

void PauseScreen::Pause()
{
	SceneTree* tree = get_tree();
	bool displaying = !tree->is_paused();
	tree->set_pause(displaying);
	set_visible(displaying);
}

PauseScreen* PauseScreen::getInstance()
{
	return instance;
}

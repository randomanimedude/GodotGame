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
	Control* options = Node::cast_to<Control>(get_node("../InGameOptions"));
	if (!options->is_visible())
	{
		SceneTree* tree = get_tree();
		bool displaying = !tree->is_paused();
		tree->set_pause(displaying);
		set_visible(displaying);
	}
	else
	{
		options->set_visible(false);
		set_visible(true);
	}
}

PauseScreen* PauseScreen::getInstance()
{
	return instance;
}

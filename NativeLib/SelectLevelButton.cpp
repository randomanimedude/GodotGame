#include "SelectLevelButton.h"

void SelectLevelButton::_register_methods()
{
	register_method("_ready", &SelectLevelButton::_ready);
	register_method("_on_Button_mouse_entered", &SelectLevelButton::_on_Button_mouse_entered);
	register_method("_on_Button_pressed", &SelectLevelButton::_on_Button_pressed);

	register_property("level_index", &SelectLevelButton::level_index, 0);
	register_property("secret_level", &SelectLevelButton::secret_level, false);}

void SelectLevelButton::_init()
{
}

void SelectLevelButton::_ready()
{
	if (!level_index)
		grab_focus();

	levelManager = Node::cast_to<LevelManager>(get_node("/root/LevelManager"));
	dataLoader = DataLoader::GetSingletone();
	if (!dataLoader->GetLevelAvailable(level_index))
	{
		set_disabled(true);
		if (secret_level)
			set_visible(false);
	}
	else
	{
		connect("mouse_entered", this, "_on_Button_mouse_entered");
		connect("pressed", this, "_on_Button_pressed");
	}
}

void SelectLevelButton::_on_Button_mouse_entered()
{
	grab_focus();
}

void SelectLevelButton::_on_Button_pressed()
{
	levelManager->LoadLevel(level_index);
}

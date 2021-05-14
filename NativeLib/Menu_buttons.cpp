#include "Menu_buttons.h"

void Menu_buttons::_register_methods()
{
	register_method("_ready", &Menu_buttons::_ready);
	register_method("_on_Button_mouse_entered", &Menu_buttons::_on_Button_mouse_entered);
	register_method("_on_Button_Pressed", &Menu_buttons::_on_Button_Pressed);


	register_property("reference_path", &Menu_buttons::reference_path, (String)"");
	register_property("start_focused", &Menu_buttons::start_focused, false);
	register_property("load_scene", &Menu_buttons::load_scene, true);
}

void Menu_buttons::_init()
{
}

void Menu_buttons::_ready()
{
	get_tree()->set_pause(false);
	if (start_focused)
	{
		grab_focus();
	}
	connect("mouse_entered", this, "_on_Button_mouse_entered");
	connect("pressed", this, "_on_Button_Pressed");
}

void Menu_buttons::_on_Button_mouse_entered()
{
	grab_focus();
}

void Menu_buttons::_on_Button_Pressed()
{
	if (load_scene)
	{
		if (reference_path != "")
		{
			if (reference_path == "res://Scenes/LvL1.tscn")
				DataLoader::GetSingleton()->ResetLevelAvailability();
			get_tree()->change_scene(reference_path);
		}
		else
			get_tree()->quit();
	}
	else
	{
		Node::cast_to<Node2D>(get_parent())->set_visible(false);
		Node::cast_to<Node2D>(get_node((NodePath)reference_path))->set_visible(true);
	}
}

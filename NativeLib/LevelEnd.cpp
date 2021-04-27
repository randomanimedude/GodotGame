#include "LevelEnd.h"

void LevelEnd::_register_methods()
{
	register_method("_ready", &LevelEnd::_ready);
	register_method("_on_body_entered", &LevelEnd::_on_body_entered);

	register_property("this_level_id", &LevelEnd::this_level_id, 0);
	register_property("next_level_id", &LevelEnd::next_level_id, 1);
}

void LevelEnd::_init()
{
}

void LevelEnd::_ready()
{
	connect("body_entered", this, "_on_body_entered");
	levelManager = Node::cast_to<LevelManager>(get_node("/root/LevelManager"));
}

void LevelEnd::_on_body_entered(PhysicsBody2D* body)
{
	if (body->get_name() == "Player")
	{
		levelManager->CompleteLevel(this_level_id);
		levelManager->LoadLevel(next_level_id);
	}
}


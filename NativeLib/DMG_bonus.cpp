#include "DMG_bonus.h"

void DMG_bonus::_register_methods()
{
	register_method("_ready", &DMG_bonus::_ready);
	register_method("_on_body_entered", &DMG_bonus::_on_body_entered);

	register_property("damage_bonus", &DMG_bonus::damage_bonus, 5);
}

void DMG_bonus::_init()
{
}

void DMG_bonus::_ready()
{
	connect("body_entered", this, "_on_body_entered");
	Node::cast_to<AnimationPlayer>(get_node("AnimationPlayer"))->play("Float");
}

void DMG_bonus::_on_body_entered(PhysicsBody2D* body)
{
	if (body->get_name() == "Player")
	{
		Player::GetInstance()->IncreaseDamage(damage_bonus);
		queue_free();
	}
}

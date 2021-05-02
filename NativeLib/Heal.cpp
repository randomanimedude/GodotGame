#include "Heal.h"

void Heal::_register_methods()
{
	register_method("_ready", &Heal::_ready);
	register_method("_on_body_entered", &Heal::_on_body_entered);

	register_property("heal", &Heal::heal, 10);
}

void Heal::_init()
{
}

void Heal::_ready()
{
	connect("body_entered", this, "_on_body_entered");
	Node::cast_to<AnimationPlayer>(get_node("AnimationPlayer"))->play("Float");
}

void Heal::_on_body_entered(PhysicsBody2D* body)
{
	if (body->get_name() == "Player")
	{
		Player::GetInstance()->Heal(heal);
		queue_free();
	}
}
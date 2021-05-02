#include "Max_HP_bonus.h"

void Max_HP_bonus::_register_methods()
{
	register_method("_ready", &Max_HP_bonus::_ready);
	register_method("_on_body_entered", &Max_HP_bonus::_on_body_entered);

	register_property("health_bonus", &Max_HP_bonus::health_bonus, 15);
	register_property("full_heal", &Max_HP_bonus::full_heal, true);
}

void Max_HP_bonus::_init()
{
}

void Max_HP_bonus::_ready()
{
	connect("body_entered", this, "_on_body_entered");
	Node::cast_to<AnimationPlayer>(get_node("AnimationPlayer"))->play("Float");
}

void Max_HP_bonus::_on_body_entered(PhysicsBody2D* body)
{
	if (body->get_name() == "Player")
	{
		Player::GetInstance()->IncreaseHP(health_bonus, full_heal);
		queue_free();
	}
}

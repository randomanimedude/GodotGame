#include "DamagingArea.h"

void DamagingArea::_register_methods()
{
	register_method("_physics_process", &DamagingArea::_physics_process);
	register_method("_ready", &DamagingArea::_ready);
	register_method("_on_body_entered", &DamagingArea::_on_body_entered);
	register_method("_on_body_exited", &DamagingArea::_on_body_exited);

	register_property("damage", &DamagingArea::damage, 20);
	register_property("impact", &DamagingArea::impact, false);

}

void DamagingArea::_init()
{
}

void DamagingArea::_ready()
{
	player = Player::GetInstance();
	connect("body_entered", this, "_on_body_entered");
	connect("body_exited", this, "_on_body_exited");
}

void DamagingArea::_physics_process(float delta)
{
	if (playerInside)
		player->DealDamage(get_global_position(), damage, impact);
	
}

void DamagingArea::_on_body_entered(PhysicsBody2D* body)
{
	if (body->get_name() == "Player")
		playerInside = true;
}

void DamagingArea::_on_body_exited(PhysicsBody2D* body)
{
	if (body->get_name() == "Player")
		playerInside = false;
}

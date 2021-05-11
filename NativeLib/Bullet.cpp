#include "Bullet.h"

void Bullet::_register_methods()
{
	register_method("_physics_process", &Bullet::_physics_process);
	register_method("_ready", &Bullet::_ready);

	register_property("bullet_speed", &Bullet::bullet_speed, 1);
}

void Bullet::_init()
{
	motion = Vector2(0, 0);
}

void Bullet::_ready()
{
	parent = Node::cast_to<Node2D>(get_parent());
	collision = Node::cast_to<CollisionShape2D>(get_node("CollisionShape2D"));
	Disable();
}

void Bullet::_physics_process(float delta)
{
	_behavior->DoStuff(this);
}

void Bullet::UpdatePosition(Vector2 position, bool facingRight, bool byPlayer)
{
	set_rotation(0);		//idk why but rotation sometimes changes for no reason
	set_global_position(position);
	motion.x = facingRight ? bullet_speed : -bullet_speed;
	set_scale(Vector2(facingRight ? 1 : -1, 1));
	this->byPlayer = byPlayer;
	set_collision_mask_bit(4, byPlayer ? false : true);


	set_collision_mask_bit(3, byPlayer ? true : false);		//enable and disable collision with player(1) or enemy(3) depending on who's bullet this is
	set_collision_mask_bit(1, byPlayer ? false : true);
}

void Bullet::Disable()
{
	collision->set_disabled(true);
	parent->hide();
	set_process(false);
	set_physics_process(false);
	enabled = false;
}

void Bullet::Enable()
{
	collision->set_disabled(false);
	parent->show();
	set_process(true);
	set_physics_process(true);
	enabled = true;
}

bool Bullet::IsEnabled()
{
	return enabled;
}

void Bullet::SetBehavior(BulletBehavior* b)
{
	_behavior = b;
}

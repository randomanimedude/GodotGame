#include "Bullet.h"

void Bullet::_register_methods()
{
	register_method("_physics_process", &Bullet::_physics_process);

	register_property("bullet_speed", &Bullet::bullet_speed, 1);
}

void Bullet::_init()
{
	motion = Vector2(0, 0);
}

void Bullet::_ready()
{
}

void Bullet::_physics_process(float delta)
{
	UpdateMotion();
}

void Bullet::UpdatePosition(Vector2 position, bool facingRight)
{
	set_global_position(position);
	motion.x = facingRight ? bullet_speed : -bullet_speed;
	set_global_scale(Vector2(facingRight ? 1 : -1, 1));
}


void Bullet::UpdateMotion()
{
	Ref<KinematicCollision2D> col = move_and_collide(motion);

	if (col != nullptr)
	{
		Node* parent = get_parent();
		parent->get_parent()->remove_child(parent);
	}
}

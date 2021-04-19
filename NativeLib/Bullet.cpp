#include "Bullet.h"

void Bullet::_register_methods()
{
	register_method("_physics_process", &Bullet::_physics_process);

	register_property("bullet_speed", &Bullet::bullet_speed, 1);
}

void Bullet::_init()
{
	motion = Vector2(0, 0);
	motion.x = facing_right ? bullet_speed : -bullet_speed;
}

void Bullet::_physics_process(float delta)
{
	UpdateMotion();
}

void Bullet::UpdateMotion()
{
	move_and_slide(motion);
}

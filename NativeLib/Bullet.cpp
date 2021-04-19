#include "Bullet.h"

void Bullet::_register_methods()
{
	register_method("_process", &Bullet::_process);

	register_property("bullet_speed", &Bullet::bullet_speed, 1000);
}

void Bullet::_init()
{
	motion = Vector2(0, 0);
	motion.x = facing_right ? bullet_speed : -bullet_speed;
}

void Bullet::_process(float delta)
{
	UpdateMotion();
}

void Bullet::UpdateMotion()
{
	move_and_collide(motion);
}

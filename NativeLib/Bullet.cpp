#include "Bullet.h"
#include "Robat.h"

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
	UpdateMotion();
}

void Bullet::UpdatePosition(Vector2 position, bool facingRight)
{
	set_rotation(0);		//idk why but rotation sometimes changes for no reason
	set_global_position(position);
	motion.x = facingRight ? bullet_speed : -bullet_speed;
	set_scale(Vector2(facingRight ? 1 : -1, 1));
}

void Bullet::Disable()
{
	collision->set_disabled(true);
	parent->hide();
	parent->set_process(false);
	parent->set_physics_process(false);
	enabled = false;
}

void Bullet::Enable()
{
	collision->set_disabled(false);
	parent->show();
	parent->set_process(true);
	parent->set_physics_process(true);
	enabled = true;
}

bool Bullet::IsEnabled()
{
	return enabled;
}


void Bullet::UpdateMotion()
{
	Ref<KinematicCollision2D> col = move_and_collide(motion);

	if (col != nullptr)
	{
		DestroyIfEnemy(col);
		Disable();
	}
}

void Bullet::DestroyIfEnemy(Ref<KinematicCollision2D> collision)
{
	Node* node = Node::cast_to<Node>(collision->get_collider());
	if (node->get_name() == "Robat")
		Object::cast_to<Robat>(node)->Destroy();
}

#include "BulletBehavior.h"

void GoodBullet::DoStuff(Bullet* bullet)
{
	Ref<KinematicCollision2D> col = bullet->move_and_collide(bullet->motion);

	if (col != nullptr)
	{
		Node* node = Node::cast_to<Node>(col->get_collider());
		if (node->get_name().find("Robat") != -1 || node->get_name().find("Rashid") != -1 || node->get_name().find("Boss") != -1)
			node->call("DealDamage", bullet->damage);

		bullet->Disable();
	}
}

void BadBullet::DoStuff(Bullet* bullet)
{
	Ref<KinematicCollision2D> col = bullet->move_and_collide(bullet->motion);

	if (col != nullptr)
	{
		Node* node = Node::cast_to<Node>(col->get_collider());
		if (node->get_name() == "Player")
			node->call("DealDamage", col->get_position(), bullet->damage, true);

		bullet->Disable();
	}
}
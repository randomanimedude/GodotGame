#include "BulletManager.h"

void BulletManager::_register_methods()
{
	register_method("_ready", &BulletManager::_ready);

	register_property("bullet_prefab", &BulletManager::bullet_prefab, Ref<PackedScene>());
	register_property("size_of_buffer", &BulletManager::size_of_buffer, 10);
	register_property("bullet_offset_x", &BulletManager::bullet_offset_x, 0);
	register_property("bullet_offset_y", &BulletManager::bullet_offset_y, 0);
}

void BulletManager::_init()
{
}

BulletManager::~BulletManager()
{
	for (auto bullet : Bullets)
		bullet->free();
	Bullets.clear();
}

void BulletManager::_ready()
{
	for (int i = 0; i < size_of_buffer; ++i)
		Bullets.push_back(Node::cast_to<Node2D>(bullet_prefab->instance()));
}

void BulletManager::SpawnNewBullet(Vector2 position, bool facingRight)
{
	for (std::vector<Node2D*>::iterator it = Bullets.begin(); it != Bullets.end(); ++it)
	{
		if ((*it)->get_parent() == nullptr)
		{
			add_child(*it);
			Node::cast_to<Bullet>((*it)->get_child(0))->UpdatePosition(position + Vector2(facingRight ? bullet_offset_x : -bullet_offset_x, bullet_offset_y), facingRight);
			break; 
		}
	}
}
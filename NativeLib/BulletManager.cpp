#include "BulletManager.h"

void BulletManager::_register_methods()
{
	register_method("_ready", &BulletManager::_ready);

	register_property("bullet_prefab", &BulletManager::bullet_prefab, Ref<PackedScene>());
	register_property("size_of_buffer", &BulletManager::size_of_buffer, 10);
	register_property("allow_expansion", &BulletManager::allow_expansion, true);
}

void BulletManager::_init()
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::_ready()
{
	for (int i = 0; i < size_of_buffer; ++i)
		AddBulletToBuffer();
}

void BulletManager::AddBulletToBuffer()
{
	Node* temp = bullet_prefab->instance();
	add_child(temp);
	Bullets.push_back(Node::cast_to<Bullet>(temp->get_child(0)));
}

void BulletManager::SpawnNewBullet(Vector2 position, bool facingRight, bool byPlayer, int damage)
{
	bool succes = false;

	//find and use free bullet
	for (Bullet* bullet : Bullets)
	{
		if (!bullet->IsEnabled())
		{
			bullet->damage = damage;
			bullet->Enable();
			bullet->UpdatePosition(position, facingRight, byPlayer);
			if(byPlayer)
				bullet->SetBehavior(&good);
			else
				bullet->SetBehavior(&bad);

			succes = true;
			break; 
		}
	}

	//if failed, add new bullet to buffer
	if (!succes && allow_expansion)
	{
		AddBulletToBuffer();
		Bullet* bullet = Bullets.back();
		bullet->damage = damage;
		bullet->Enable();
		bullet->UpdatePosition(position, facingRight, byPlayer);
		if (byPlayer)
			bullet->SetBehavior(&good);
		else
			bullet->SetBehavior(&bad);
	}
}
#include "BulletManager.h"

void BulletManager::_register_methods()
{
	register_property("bullet_prefab", &BulletManager::bullet_prefab, Ref<PackedScene>());
}

void BulletManager::_init()
{
	//loader = ResourceLoader::get_singleton();
	//bullet_prefab = loader->load((godot::String)"res://Prefabs/BulletPrefab.tscn", "PackedScene");
}

BulletManager::~BulletManager()
{
	for (auto bullet : Bullets)
		bullet->free();
	Bullets.clear();
}

void BulletManager::SpawnNewBullet(Vector2 position, bool fasingRight)
{
	Bullets.push_back(Node::cast_to<Node2D>(bullet_prefab->instance()));
	Bullets.back()->set_global_position(position);
	add_child(Bullets.back());
}
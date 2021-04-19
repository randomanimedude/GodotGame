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

void BulletManager::SpawnNewBullet()
{
	Bullets.push_back(bullet_prefab->instance());
}
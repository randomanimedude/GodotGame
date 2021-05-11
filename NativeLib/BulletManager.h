#pragma once

#include "CommonLib.h"
#include "Bullet.h"
#include "BulletBehavior.h"

#include <Node2D.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <vector>
#include <memory>


class BulletManager : public Node2D
{
	//godot structure
	GODOT_CLASS(BulletManager, Node2D);

	//exposed vars
	int size_of_buffer = 10;
	bool allow_expansion = true;
	Ref<PackedScene> bullet_prefab;

public:
	static void _register_methods();
	void _init();
	void _ready();

	~BulletManager();

	//gayplay vars
public:

private:
	std::vector<Bullet*> Bullets;
	BadBullet bad;
	GoodBullet good;

	//gayplay methods
public:
	void SpawnNewBullet(Vector2, bool, bool, int);

private:
	void AddBulletToBuffer();

};


#pragma once

#include <Godot.hpp>
#include <Node2D.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <vector>
#include <memory>

#include "Bullet.h"

using namespace godot;

class BulletManager : public Node2D
{
	//godot structure
	GODOT_CLASS(BulletManager, Node2D);

	//exposed vars
	int size_of_buffer = 10;
	bool allow_expansion = true;
	int bullet_offset_x = 0;
	int bullet_offset_y = 0;
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

	//gayplay methods
public:
	void SpawnNewBullet(Vector2, bool);

private:
	void AddBulletToBuffer();

};


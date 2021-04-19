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
	//ResourceLoader* loader; 
	Ref<PackedScene> bullet_prefab;

public:
	static void _register_methods();
	void _init();

	~BulletManager();

	//gayplay vars
public:

private:
	std::vector<Node2D*> Bullets;

	//gayplay methods
public:
	void SpawnNewBullet(Vector2, bool);

private:

};


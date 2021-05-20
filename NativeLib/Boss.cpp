#include "Boss.h"

void Boss::_register_methods()
{
	register_method("_ready", &Boss::_ready);
	register_method("SpawnEnemy", &Boss::SpawnEnemy);
	register_method("DealDamage", &Boss::DealDamage);

	register_property("HP", &Boss::HP, 200);
	register_property("damage", &Boss::damage, 15);
	register_property("score_reward", &Boss::score_reward, 1);
}

void Boss::_init()
{
	srand(time(0));
}

void Boss::_ready()
{
	spawnPosition1 = Node::cast_to<Node2D>(get_node("SpawnPos1"))->get_global_position();
	spawnPosition2 = Node::cast_to<Node2D>(get_node("SpawnPos2"))->get_global_position();
	spawnPosition3 = Node::cast_to<Node2D>(get_node("SpawnPos3"))->get_global_position();

	animator = Node::cast_to<AnimationPlayer>(get_node("AnimationPlayer"));

	ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
	rashid = resourceLoader->load("res://Prefabs/Enemies/Rashid.tscn");
	robat = resourceLoader->load("res://Prefabs/Enemies/Robat.tscn");

	move_and_slide_with_snap(Vector2(0, 100), Vector2(0, -1), Vector2(0, 100));		//move to ground
	animator->play("Call");
}

void Boss::SpawnEnemy(int index)
{
	switch (index)
	{
	case 0:
		Spawn(spawnPosition1);
		break;
	case 1:
		Spawn(spawnPosition2);
		break;
	case 2:
		Spawn(spawnPosition3);
	}
}

void Boss::DealDamage(int damage)
{
}

void Boss::Spawn(Vector2 position)
{
	Node2D* temp;
	if (rand() % 2)
	{
		temp = Node::cast_to<Node2D>(robat->instance());
	}
	else
	{
		temp = Node::cast_to<Node2D>(rashid->instance());
	}
	get_parent()->add_child(temp);
	temp->set_global_position(position);
	cout << "spawn at " << position.x << endl;
}

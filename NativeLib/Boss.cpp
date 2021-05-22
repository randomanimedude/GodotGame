#include "Boss.h"

void Boss::_register_methods()
{
	register_method("_ready", &Boss::_ready);
	register_method("_physics_process", &Boss::_physics_process);
	register_method("_on_body_entered", &Boss::_on_body_entered);
	register_method("SpawnEnemy", &Boss::SpawnEnemy);
	register_method("DealDamage", &Boss::DealDamage);
	register_method("OpenWindow", &Boss::OpenWindow);

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

	playerDetector = Node::cast_to<RayCast2D>(get_node("PlayerDetector"));
	minionDetector1 = Node::cast_to<RayCast2D>(get_node("MinionDetector1"));
	minionDetector2 = Node::cast_to<RayCast2D>(get_node("MinionDetector2"));
	minionDetector3 = Node::cast_to<RayCast2D>(get_node("MinionDetector3"));

	animator = Node::cast_to<AnimationPlayer>(get_node("AnimationPlayer"));

	maxHP = HP;
	healthBar = Node::cast_to<EnemyHealthBar>(get_node("CollisionShape2D/EnemyHealthBar"));
	healthBar->SetProgress(HP, maxHP);

	damagingArea = Node::cast_to<Area2D>(get_node("CollisionShape2D/Area2D"));
	damagingArea->connect("body_entered", this, "_on_body_entered");

	ResourceLoader* resourceLoader = ResourceLoader::get_singleton();
	rashid = resourceLoader->load("res://Prefabs/Enemies/Rashid.tscn");
	robat = resourceLoader->load("res://Prefabs/Enemies/Robat.tscn");

	move_and_slide_with_snap(Vector2(0, 100), Vector2(0, -1), Vector2(0, 100));		//move to ground
	animator->play("Idle");
}

void Boss::_physics_process(float delta)
{
	if (!active && playerDetector->is_colliding())			//activate only when player arrives
	{
		active = true;
		RandomAtack();
	}

	if (active && (string)animator->get_current_animation().alloc_c_string() == (string)"Idle" && (waitTime -= delta) <= 0)
		RandomAtack();
}

void Boss::SpawnEnemy(int index)
{
	switch (index)
	{
	case 0:
		if(!minionDetector1->is_colliding())
			Spawn(spawnPosition1);
		break;
	case 1:
		if (!minionDetector2->is_colliding())
			Spawn(spawnPosition2);
		break;
	case 2:
		if (!minionDetector3->is_colliding())
			Spawn(spawnPosition3);
	}
}

void Boss::DealDamage(int damage)
{
	HP -= damage;
	cout << HP << endl;
	healthBar->SetProgress(HP, maxHP);
	if (HP <= 0)
		Die();
}

void Boss::OpenWindow()
{
	waitTime = rand() % 3 + 2;			//2-4 sec window between atacks
	animator->play("Idle");
}

void Boss::RandomAtack()
{
	switch (rand() % 2)
	{
	case 0:
		animator->play("Call");
		break;
	case 1:
		animator->play("Roll");
	}
}

void Boss::DamagePlayer()
{
	Player::GetInstance()->DealDamage(get_global_position(), damage, true);
}

void Boss::_on_body_entered(PhysicsBody2D* body)
{
	if (body->get_name() == "Player")
		DamagePlayer();
}

void Boss::Spawn(Vector2 position)
{
	Node2D* temp;
	if (rand() % 2)
	{
		temp = Node::cast_to<Node2D>(robat->instance());
		Node::cast_to<Robat>(temp)->SetReward(0);
		temp->set_global_scale(robatScale);
	}
	else
	{
		temp = Node::cast_to<Node2D>(rashid->instance());
		Node::cast_to<Rashid>(temp)->SetReward(0);
		temp->set_global_scale(rashidScale);
	}
	get_parent()->add_child(temp);
	temp->set_global_position(position);
}

void Boss::Die()
{
	Player::GetInstance()->AddScore(score_reward);
	queue_free();
}

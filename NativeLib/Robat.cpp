#include "Robat.h"

using namespace std;

void Robat::_register_methods()
{
	register_method("_ready", &Robat::_ready);
	register_method("_physics_process", &Robat::_physics_process);
	register_method("DealDamage", &Robat::DealDamage);
	register_method("ShootLeft", &Robat::ShootLeft);
	register_method("ShootRight", &Robat::ShootRight);

	register_property("max_speed", &Robat::max_speed, 800);
	register_property("move", &Robat::move, true);
	register_property("gravity", &Robat::gravity, 70);
	register_property("max_fall_speed", &Robat::max_fall_speed, 1200);
	register_property("acceleration", &Robat::acceleration, 50);
	register_property("zanos", &Robat::zanos, 0.2f);
	register_property("HP", &Robat::HP, 15);
	register_property("damage", &Robat::damage, 10);
	register_property("score_reward", &Robat::score_reward, 10);
}

void Robat::_init()
{
	motion = Vector2(0, 0);
}

void Robat::_ready()
{
	max_hp = HP;
	scale = get_scale();
	animator = Node::cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	floorDetector = Node::cast_to<RayCast2D>(get_node("FloorDetector"));
	playerDetector = Node::cast_to<RayCast2D>(get_node("PlayerDetector"));
	bulletSpawnPositionLeft = Node::cast_to<Node2D>(get_node("BulletSpawnPositionLeft"));
	bulletSpawnPositionRight = Node::cast_to<Node2D>(get_node("BulletSpawnPositionRight"));
	bulletManager = Node::cast_to<BulletManager>(get_node("../BulletManager"));
	healthBar = Node::cast_to<EnemyHealthBar>(get_node("EnemyHealthBar"));
	healthBar->SetProgress(HP, HP);

	facing_right = get_scale().x < 0;
	if (facing_right) healthBar->TurnAround();
}

void Robat::_physics_process(float delta)
{
	if (move)
		TurnAroundIfNeeded();
	Move();
	ShootAtSight();
	if (!isShooting)
		animator->play("Move");
}

void Robat::DealDamage(int dmg)
{
	HP -= dmg;
	healthBar->SetProgress(HP, max_hp);
	if (HP <= 0)
		Die();
}

void Robat::ShootLeft()
{
	bulletManager->SpawnNewBullet(bulletSpawnPositionLeft->get_global_position(), facing_right, false, damage);
}

void Robat::ShootRight()
{
	bulletManager->SpawnNewBullet(bulletSpawnPositionRight->get_global_position(), facing_right, false, damage);
}

void Robat::SetReward(int reward)
{
	score_reward = reward;
}

void Robat::ShootAtSight()
{
	if (playerDetector->is_colliding())
	{
		animator->play((String)"Shoot");
		isShooting = true;
	}
	else
		isShooting = false;
}

void Robat::Move()
{
	set_rotation(0);

	motion.y += gravity;
	motion.y = clamp(motion.y, 0, max_fall_speed);

	if (!isShooting && move)
	{
		animator->play("Move");
		motion.x += facing_right ? acceleration : -acceleration;
	}
	else
		motion.x = lerp((float)motion.x, (float)0, zanos);
	motion.x = clamp(motion.x, -max_speed, max_speed) * is_on_floor();

	set_scale(Vector2(facing_right ? -abs(scale.x) : abs(scale.x), scale.y));
	motion = move_and_slide_with_snap(motion, Vector2(0,32), UP);
}

void Robat::TurnAroundIfNeeded()
{
	if ((is_on_wall() || !floorDetector->is_colliding()) && is_on_floor())
	{
		facing_right = !facing_right;
		healthBar->TurnAround();
	}
}

void Robat::Die()
{
	Player::GetInstance()->AddScore(score_reward);
	queue_free();
}

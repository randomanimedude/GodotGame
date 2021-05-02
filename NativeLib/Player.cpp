#include "Player.h"
#include <cmath>

using namespace godot;

void Player::_register_methods()
{
	register_method("_process", &Player::_process);
	register_method("_physics_process", &Player::_physics_process);
	register_method("_ready", &Player::_ready);
	register_method("DealDamage", &Player::DealDamage);
	register_method("ShootRight", &Player::ShootRight);
	register_method("ShootLeft", &Player::ShootLeft);

	register_property("max_speed", &Player::max_speed, 800);
	register_property("zanos", &Player::zanos, 0.2f);
	register_property("gravity", &Player::gravity, 70);
	register_property("max_fall_speed", &Player::max_fall_speed, 1200);
	register_property("jump_force", &Player::jump_force, 1600);
	register_property("acceleration", &Player::acceleration, 50); 
	register_property("hit_impact_x", &Player::hit_impact_x, 300);
	register_property("hit_impact_y", &Player::hit_impact_y, -300);
	register_property("max_HP", &Player::max_HP, 100);
	register_property("starting_damage", &Player::starting_damage, 10);
}

void Player::_init()
{
	instance = this;
	inp = Input::get_singleton();
	HP = max_HP;
	damage = starting_damage;
}

void Player::_ready()
{
	animator = Node::cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	bulletManager = Node::cast_to<BulletManager>(get_node("../BulletManager"));
	bulletSpawnPositionRight = Node::cast_to<Node2D>(get_node("BulletSpawnPositionRight"));
	bulletSpawnPositionLeft = Node::cast_to<Node2D>(get_node("BulletSpawnPositionLeft"));
	interfaceManager = Node::cast_to<InterfaceManager>(get_node("UI/Interface"));

	interfaceManager->SetDMG(damage);
	interfaceManager->SetHP(HP, max_HP);
	interfaceManager->SetScore(0);
}

void Player::_process(float delta)
{
}

void Player::_physics_process(float delta)
{
	UpdateMotionFromInput();
	motion = move_and_slide_with_snap(motion, Vector2(0, jumping ? 0 : 32), UP);
}

void Player::DealDamage(Vector2 hitPoint, int dmg, bool commitImpact)
{
	if (!dead)
	{
		if ((HP -= dmg) <= 0)
			Die();
		else if (commitImpact)
		{
			jumping = true;
			motion.x = (hitPoint.x < get_position().x) ? hit_impact_x : -hit_impact_x;
			motion.y = hit_impact_y;
		}
	}
	interfaceManager->SetHP(HP, max_HP);
}

void Player::ShootRight()
{
	bulletManager->SpawnNewBullet(bulletSpawnPositionRight->get_global_position(), true, true, damage);
}

void Player::ShootLeft()
{
	bulletManager->SpawnNewBullet(bulletSpawnPositionLeft->get_global_position(), false, true, damage);
}

void Player::UpdateMotionFromInput()
{
	motion.y += gravity;
	motion.y = clamp(motion.y, -jump_force, max_fall_speed);

	if (motion.y > 0)
		jumping = false;

	if (!dead && animator->get_current_animation().find("Shoot") == -1)
	{
		//jumping part
		if (is_on_floor())
		{
			if (inp->is_action_just_pressed("jump"))
			{
				motion.y = -jump_force;
				jumping = true;
			}
			if (motion.x == 0)
				animator->play((godot::String)"Idle" + (godot::String)(facing_right ? "Right" : "Left"));
		}
		if (inp->is_action_just_released("jump") && motion.y <= -jump_force / 2)
			motion.y = -jump_force / 2;

		//moving left-right part
		if (inp->is_action_pressed("move_left") && !inp->is_action_pressed("move_right"))
		{
			if (motion.x > 0) motion.x = lerp((float)motion.x, (float)0, zanos);
			motion.x -= acceleration;
			facing_right = false;
			animator->play("RunLeft");
		}
		else if (inp->is_action_pressed("move_right") && !inp->is_action_pressed("move_left"))
		{
			if (motion.x < 0) motion.x = lerp((float)motion.x, (float)0, zanos);
			motion.x += acceleration;
			facing_right = true;
			animator->play("RunRight");
		}
		else if (is_on_floor())
		{
			motion.x = lerp((float)motion.x, (float)0, zanos);
			if (motion.x < 1) motion.x = 0;
		}
		motion.x = clamp(motion.x, -max_speed, max_speed);

		// jump/fall animation 
		if (motion.y > gravity && !is_on_floor())
			animator->play("Fall" + (godot::String)(facing_right ? "Right" : "Left"));
		else if (motion.y < gravity)
			animator->play("Jump" + (godot::String)(facing_right ? "Right" : "Left"));

		//shooting part
		if (inp->is_action_just_pressed("shoot"))
			animator->play((godot::String)"Shoot" + (godot::String)(facing_right ? "Right" : "Left"));
	}
	else if (is_on_floor())
		motion.x = 0;
}

void Player::IncreaseHP(int hp, bool full_heal)
{
	max_HP += hp;
	Heal(full_heal ? max_HP : hp);
}

void Player::Die()
{
	dead = true;
	animator->play((godot::String)"Death" + (godot::String)(facing_right ? "Right" : "Left"));
}

void Player::AddScore(int num)
{
	score += num;
	interfaceManager->SetScore(score);
}

void Player::IncreaseDamage(int bonus)
{
	damage += bonus;
	interfaceManager->SetDMG(damage);
}

Player* Player::GetInstance()
{
	return instance;
}

void Player::Heal(int hp)
{
	HP += hp;
	if (HP > max_HP)
		HP = max_HP;
	interfaceManager->SetHP(HP, max_HP);
}

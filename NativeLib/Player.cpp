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
	register_method("StopGame", &Player::StopGame);

	register_property("max_speed", &Player::max_speed, 800);
	register_property("zanos", &Player::zanos, 0.2f);
	register_property("gravity", &Player::gravity, 70);
	register_property("max_fall_speed", &Player::max_fall_speed, 1200);
	register_property("jump_force", &Player::jump_force, 1600);
	register_property("acceleration", &Player::acceleration, 50); 
	register_property("hit_impact_x", &Player::hit_impact_x, 300);
	register_property("hit_impact_y", &Player::hit_impact_y, -300);
	register_property("damage_cooldown", &Player::damage_cooldown, 1.0f);
	register_property("max_HP", &Player::max_HP, 100);
	register_property("starting_damage", &Player::starting_damage, 10);
}

void Player::_init()
{
	instance = this;
	inp = Input::get_singleton();
	cout << 'a';
}

void Player::_ready()
{
	animator = Node::cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	bulletManager = Node::cast_to<BulletManager>(get_node("../BulletManager"));
	bulletSpawnPositionRight = Node::cast_to<Node2D>(get_node("BulletSpawnPositionRight"));
	bulletSpawnPositionLeft = Node::cast_to<Node2D>(get_node("BulletSpawnPositionLeft"));
	interfaceManager = Node::cast_to<InterfaceManager>(get_node("UI/Interface"));

	HP = max_HP;
	damage = starting_damage;
	interfaceManager->SetDMG(damage);
	interfaceManager->SetHP(HP, max_HP);
	interfaceManager->SetScore(0);
	cout << 'b';
}

void Player::_process(float delta)
{
}

void Player::_physics_process(float delta)
{
	if (damaged)
	{
		damagedFor += delta;
		if (damagedFor >= damage_cooldown)
		{
			damagedFor = 0;
			damaged = false;
		}
	}
	UpdateMotionFromInput();
	motion = (jumping || impact) ? move_and_slide(motion, UP) : move_and_slide_with_snap(motion, Vector2(0, 32), UP);
}

void Player::DealDamage(Vector2 hitPoint, int dmg, bool commitImpact)
{
	if (!damaged)
	{
		if (!dead)
		{
			if ((HP -= dmg) <= 0)
				Die();
			else 
			{
				if (commitImpact)
				{
					jumping = true;
					motion.x = (hitPoint.x < get_position().x) ? hit_impact_x : -hit_impact_x;
					motion.y = hit_impact_y;
					animator->play((String)"Fall" + (String)((motion.x < 0) ? "Right" : "Left"));
					facing_right = (motion.x < 0) ? true : false;
				}
			}
		}
		interfaceManager->SetHP(HP, max_HP);
		damaged = true;
		if(commitImpact)
			impact = 2;
	}
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
	motion.y = clamp(motion.y, -9999999, max_fall_speed);

	if (inp->is_action_just_released("jump") && motion.y <= -jump_force / 2 && jumping && !impact)
		motion.y = -jump_force / 2;

	if (is_on_floor())
	{
		if(impact > 0)
			impact -= 1;
		jumping = false;
	}

	if (!dead && animator->get_current_animation().find("Shoot") == -1 && !impact)
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
			if (abs(motion.x) < 1) motion.x = 0;
		}
		motion.x = clamp(motion.x, -max_speed, max_speed);

		// jump/fall animation 
		if (motion.y > gravity && !is_on_floor())
			animator->play("Fall" + (godot::String)(facing_right ? "Right" : "Left"));
		else if (motion.y < gravity && !Node::cast_to<AudioStreamPlayer>(get_node("SFX/Jump"))->is_playing())
			animator->play("Jump" + (godot::String)(facing_right ? "Right" : "Left"));
		if (!jumping)
			Node::cast_to<AudioStreamPlayer>(get_node("SFX/Jump"))->stop();

		//shooting part
		if (inp->is_action_just_pressed("shoot"))
			animator->play((godot::String)"Shoot" + (godot::String)(facing_right ? "Right" : "Left"));
	}
	else if (is_on_floor() && !impact)
		motion.x = 0;
}

void Player::IncreaseHP(int hp, bool full_heal)
{
	max_HP += hp;
	Heal(full_heal ? max_HP : hp);
	Node::cast_to<AudioStreamPlayer>(get_node("SFX/PickUpBoost"))->play();
}

void Player::StopGame()
{
	get_tree()->set_pause(true);
	Node::cast_to<Control>(get_node("UI/GameOver/GameOver"))->set_visible(true);
}

int Player::GetScore()
{
	return score;
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
	Node::cast_to<AudioStreamPlayer>(get_node("SFX/PickUpBoost"))->play();
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
	Node::cast_to<AudioStreamPlayer>(get_node("SFX/PickUpBoost"))->play();
}

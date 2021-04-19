#include "Player.h"
#include <cmath>

using namespace godot;

void Player::_register_methods()
{
	register_method("_process", &Player::_process);
	register_method("_physics_process", &Player::_physics_process);
	register_method("_ready", &Player::_ready);

	register_property("max_speed", &Player::max_speed, 300);
	register_property("zanos", &Player::zanos, 0.2f);
	register_property("gravity", &Player::gravity, 20);
	register_property("max_fall_speed", &Player::max_fall_speed, 400);
	register_property("jump_force", &Player::jump_force, 500);
	register_property("acceleration", &Player::acceleration, 20);
}

void Player::_init()
{
	oldMotion = motion = Vector2(0, 0);

	inp = Input::get_singleton();
}

void Player::_ready()
{
	nodeFinder = get_node("AnimationPlayer");
	animator = Node::cast_to<AnimationPlayer>(nodeFinder);
	nodeFinder = get_node("BulletManager");
	bulletManager = Node::cast_to<BulletManager>(nodeFinder);
}

void Player::_process(float delta)
{
}

void Player::_physics_process(float delta)
{
	UpdateMotionFromInput();
	motion = move_and_slide(motion, UP);
}

void Player::UpdateMotionFromInput()
{
	
	motion.y += gravity;
	motion.y = clamp(motion.y, -jump_force, max_fall_speed);

	if (animator->get_current_animation().find("Shoot") == -1)
	{
		if (is_on_floor())
		{
			if (inp->is_action_just_pressed("jump"))
				motion.y = -jump_force;

			if (motion.x == 0)
				animator->play((godot::String)"Idle" + (godot::String)(facing_right ? "Right" : "Left"));
		}

		if (inp->is_action_pressed("move_left") && !inp->is_action_pressed("move_right"))
		{
			motion.x -= acceleration;
			facing_right = false;
			animator->play("RunLeft");
		}
		else if (inp->is_action_pressed("move_right") && !inp->is_action_pressed("move_left"))
		{
			motion.x += acceleration;
			facing_right = true;
			animator->play("RunRight");
		}
		else
			motion.x = std::lerp((float)motion.x, (float)0, zanos);
		motion.x = clamp(motion.x, -max_speed, max_speed);


		if (inp->is_action_just_pressed("shoot"))
		{
			animator->play((godot::String)"Shoot" + (godot::String)(facing_right ? "Right" : "Left"));
			bulletManager->SpawnNewBullet();
		}
	}
	else if (is_on_floor())
		motion.x = 0;
}

int Player::clamp(int x, int min, int max)
{
	return (x < min) ? min : ((x > max) ? max : x);
}

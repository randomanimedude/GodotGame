#include "Player.h"
#include <cmath>

using namespace godot;

void Player::_register_methods()
{
	register_method("_physics_process", &Player::_physics_process);
	register_method("_ready", &Player::_ready);

	register_property("max_speed", &Player::max_speed, 300);
	register_property("gravity", &Player::gravity, 20);
	register_property("max_fall_speed", &Player::max_fall_speed, 400);
	register_property("jump_force", &Player::jump_force, 500);
	register_property("acceleration", &Player::acceleration, 20);
}

void Player::_init()
{
	motion = Vector2(0, 0);
}

void Player::_ready()
{
	node = get_node("AnimationPlayer");
	animator = Node::cast_to<AnimationPlayer>(node);
}

void Player::_physics_process(float delta)
{
	UpdateMotionFromInput();
}

void Player::UpdateMotionFromInput()
{
	
	motion.y += gravity;
	motion.y = clamp(motion.y, -jump_force, max_fall_speed);

	Input* inp = Input::get_singleton();

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
		motion.x = 0;// std::lerp((float)motion.x, (float)0, (float)0.2);
	motion.x = clamp(motion.x, -max_speed, max_speed);

	if (is_on_floor() && inp->is_action_pressed("jump"))
		motion.y = -jump_force;

	motion = move_and_slide(motion, UP);

	if (is_on_floor() && motion.x == 0)
		animator->play((godot::String)"Idle" + (godot::String)(facing_right ? "Right" : "Left"));
}

int Player::clamp(int x, int min, int max)
{
	return (x < min) ? min : ((x > max) ? max : x);
}

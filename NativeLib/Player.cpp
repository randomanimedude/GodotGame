#include "Player.h"
#include <cmath>

using namespace godot;

void Player::_register_methods()
{
	register_method((char*)"_process", &Player::_physics_process);
}

void Player::_init()
{
}

void Player::_physics_process(float delta)
{
	UpdateMotionFromInput();
}

Player::Player()
{
	motion = Vector2(0, 0);
}

Player::~Player()
{
}

void Player::UpdateMotionFromInput()
{
	motion.y += GRAVITY;
	motion.y = clamp(motion.y, -JUMPFORCE, MAXFALLSPEED);

	Input* inp = Input::get_singleton();

	if (inp->is_action_pressed("move_left") && !inp->is_action_pressed("move_right"))
		motion.x -= ACCELERATION;
	else if (inp->is_action_pressed("move_right") && !inp->is_action_pressed("move_left"))
		motion.x += ACCELERATION;
	else
		motion.x = std::lerp((float)motion.x, (float)0, (float)0.2);
	motion.x = clamp(motion.x, -MAXSPEED, MAXSPEED);

	if (is_on_floor() && inp->is_action_pressed("jump"))
		motion.y = -JUMPFORCE;

	motion = move_and_slide(motion, UP);
}

int Player::clamp(int x, int min, int max)
{
	return (x < min) ? min : ((x > max) ? max : x);
}

#include "Player.h"

using namespace godot;

void Player::_register_methods()
{
	register_method((char*)"_process", &Player::_process);
}

void Player::_init()
{
}

void Player::_process(float delta)
{
	UpdateMotionFromInput();
	move_and_slide(motion);
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
	motion = Vector2(0, 0);

	Input* inp = Input::get_singleton();

	if (inp->is_action_pressed("ui_up"))
		motion.y -= speed;
	if (inp->is_action_pressed("ui_down"))
		motion.y += speed;
	if (inp->is_action_pressed("ui_left"))
		motion.x -= speed;
	if (inp->is_action_pressed("ui_right"))
		motion.x += speed;
}

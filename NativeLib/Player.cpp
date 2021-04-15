#include "Player.h"
#include <cmath>

using namespace godot;

void Player::_register_methods()
{
	register_method("_physics_process", &Player::_physics_process);
	register_method("_ready", &Player::_ready);
}

void Player::_init()
{
	motion = Vector2(0, 0);
}

void Player::_ready()
{
	node = get_node("AnimationPlayer");
	animator = Node::cast_to<AnimationPlayer>(node);
	std::cout << (animator == nullptr);
}

void Player::_physics_process(float delta)
{
	UpdateMotionFromInput();
}

Player::Player()
{
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
	{
		motion.x -= ACCELERATION;
		facing_right = false;
		animator->play("RunLeft");
	}
	else if (inp->is_action_pressed("move_right") && !inp->is_action_pressed("move_left"))
	{
		motion.x += ACCELERATION;
		facing_right = true;
		animator->play("RunRight");
	}
	else
		motion.x = 0;// std::lerp((float)motion.x, (float)0, (float)0.2);
	motion.x = clamp(motion.x, -MAXSPEED, MAXSPEED);

	if (is_on_floor() && inp->is_action_pressed("jump"))
		motion.y = -JUMPFORCE;

	motion = move_and_slide(motion, UP);

	if (is_on_floor() && motion.x == 0)
		animator->play((godot::String)"Idle" + (godot::String)(facing_right ? "Right" : "Left"));
}

int Player::clamp(int x, int min, int max)
{
	return (x < min) ? min : ((x > max) ? max : x);
}

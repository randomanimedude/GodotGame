#include "Robat.h"

void Robat::_register_methods()
{
	register_method("_ready", &Robat::_ready);
	register_method("_process", &Robat::_process);
	register_method("_physics_process", &Robat::_physics_process);

	register_property("max_speed", &Robat::max_speed, 800);
	register_property("gravity", &Robat::gravity, 70);
	register_property("max_fall_speed", &Robat::max_fall_speed, 1200);
	register_property("acceleration", &Robat::acceleration, 50);
}

void Robat::_init()
{
	motion = Vector2(0, 0);
}

void Robat::_ready()
{
	scale = get_scale();
	nodeFinder = get_node("AnimationPlayer");
	animator = Node::cast_to<AnimationPlayer>(nodeFinder);
}

void Robat::_process(float delta)
{
}

void Robat::_physics_process(float delta)
{
	MoveFromWallToWall();
}

void Robat::Destroy()
{
	queue_free();
}

void Robat::MoveFromWallToWall()
{
	set_rotation(0);

	motion.y += gravity;
	motion.y = clamp(motion.y, 0, max_fall_speed);

	motion.x += facing_right ? acceleration : -acceleration;
	motion.x = clamp(motion.x, -max_speed, max_speed);

	set_scale(Vector2(facing_right ? -scale.x : scale.x, scale.y));

	motion = move_and_slide(motion, UP);

	if (is_on_wall())
		facing_right = !facing_right;
}

#include "Platform.h"

void Platform::_register_methods()
{
	register_method("_ready", &Platform::_ready);
	register_method("_physics_process", &Platform::_physics_process);

	//register_property("max_speed_x", &Platform::max_speed_x, 100);
	//register_property("max_speed_y", &Platform::max_speed_y, 100);
	//register_property("acceleration_x", &Platform::acceleration_x, 10);
	//register_property("acceleration_y", &Platform::acceleration_y, 10);
	register_property("Acceleration(%)", &Platform::acceleration, 1.0f);
	register_property("Max speed(%)", &Platform::max_speed, 1.0f);
}

void Platform::_init()
{
}

void Platform::_ready()
{
	start = get_global_position();
	end = Node::cast_to<Node2D>(get_node("EndPosition"))->get_global_position();
	cout << ((end - start) * max_speed / 100).x << ' ' << ((end - start) * max_speed / 100).y;
	accelerationVector = (end - start) * acceleration / 100;
	maxSpeedVector = (end - start) * max_speed / 100;
	motion = Vector2(0, 0);
	endIsBelow = motion.y > 0;
	endIsOnRigh = motion.x > 0;
}

void Platform::_physics_process(float delta)
{
	currentPosition = get_global_position();
	GoBack();
	Move();

	//if (toEnd)
	//{
	//	motion += Vector2(acceleration_x* ((endIsOnRigh && toEnd )?1:-1), acceleration_y)
	//	motion.x = clamp(motion.x, -acceleration_x, acceleration_x);
	//	motion.y = clamp(motion.y, -acceleration_y, acceleration_y);
	//}
}

void Platform::Move()
{
	//cout << maxSpeedVector.x << ' ' << maxSpeedVector.y << endl;
	motion += toEnd ? accelerationVector : -accelerationVector;
	motion.x = clamp(motion.x, -abs(maxSpeedVector.x), abs(maxSpeedVector.x));
	motion.y = clamp(motion.y, -abs(maxSpeedVector.y), abs(maxSpeedVector.y));
	set_global_position(currentPosition + motion);
}

void Platform::GoBack()
{
	Vector2 dif;
	if (toEnd)
	{
		dif = end - currentPosition;
		if (dif.x*(endIsOnRigh?1:-1) <= 0 && dif.y * (endIsBelow ? 1 : -1) <= 0)
			toEnd = !toEnd;
	}
	else
	{
		dif = currentPosition - start;
		if (dif.x * (endIsOnRigh ? 1 : -1) <= 0 && dif.y * (endIsBelow ? 1 : -1) <= 0)
			toEnd = !toEnd;
	}


}

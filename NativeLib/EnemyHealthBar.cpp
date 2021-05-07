#include "EnemyHealthBar.h"

void EnemyHealthBar::_register_methods()
{ 
}

void EnemyHealthBar::_init()
{
}

void EnemyHealthBar::_ready()
{
	if (Node::cast_to<Node2D>(get_parent())->get_scale().x < 0)
		TurnAround();
}

void EnemyHealthBar::TurnAround()
{
	Vector2 scale = get_scale();
	scale.x *= -1;
	set_scale(scale);
}

void EnemyHealthBar::SetProgress(int current, int max)
{
	set_value((float)current / max * 100);
}

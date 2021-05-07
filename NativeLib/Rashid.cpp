#include "Rashid.h"

void Rashid::_register_methods()
{
	register_method("_ready", &Rashid::_ready);
	register_method("_physics_process", &Rashid::_physics_process);
	register_method("DealDamage", &Rashid::DealDamage);
	register_method("_on_body_entered_detector", &Rashid::_on_body_entered_detector);
	register_method("_on_body_entered_damageDealer", &Rashid::_on_body_entered_damageDealer);

	register_property("damage", &Rashid::damage, 10);
	register_property("score_reward", &Rashid::score_reward, 10);
	register_property("health", &Rashid::health, 30);
}

void Rashid::_init()
{
}

void Rashid::_ready()
{
	max_hp = health;

	detector = Node::cast_to<Area2D>(get_node("Detector"));
	damageDealer = Node::cast_to<Area2D>(get_node("DamageDealer"));
	animator = Node::cast_to<AnimationPlayer>(get_node("AnimationPlayer"));
	animator->play("Idle");
	healthBar = Node::cast_to<EnemyHealthBar>(get_node("EnemyHealthBar"));
	healthBar->SetProgress(health, health);

	detector->connect("body_entered", this, "_on_body_entered_detector");
	damageDealer->connect("body_entered", this, "_on_body_entered_damageDealer");
}

void Rashid::_physics_process(float delta)
{
	move_and_slide(Vector2(0, 1000));			//move to ground if placed mid-air
}

void Rashid::_on_body_entered_detector(PhysicsBody2D* body)
{
	if (!triggered && body->get_name()=="Player")
	{
		triggered = true;
		animator->play("Detect");
	}
}

void Rashid::_on_body_entered_damageDealer(PhysicsBody2D* body)
{
	if (body->get_name() == "Player")
		Player::GetInstance()->DealDamage(damageDealer->get_global_position(), damage, true);
}

void Rashid::DealDamage(int dmg)
{
	health -= dmg;
	healthBar->SetProgress(health, max_hp);
	if (health <= 0)
		Die();
}

void Rashid::Die()
{
	Player::GetInstance()->AddScore(score_reward);
	queue_free();
}

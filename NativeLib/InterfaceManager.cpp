#include "InterfaceManager.h"

void InterfaceManager::_register_methods()
{
	register_method("_ready", &InterfaceManager::_ready);
}

void InterfaceManager::_init()
{
}

void InterfaceManager::_ready()
{
	HP = Node::cast_to<Counter>(get_node("HP"));
	HPBar = Node::cast_to<TextureProgress>(get_node("HP/LifeBar"));
	DMG = Node::cast_to<Counter>(get_node("Damage"));
	Score = Node::cast_to<Counter>(get_node("Score"));
}

void InterfaceManager::SetHP(int current, int max)
{
	HP->SetValue(String::num_int64(current)+(String)'/'+ String::num_int64(max));
	HPBar->set_value((float)current / max * 63);		//63 is a maximum value set in textureProgress
}

void InterfaceManager::SetDMG(int damage)
{
	DMG->SetValue(String::num_int64(damage));
}

void InterfaceManager::SetScore(int score)
{
	Score->SetValue(String::num_int64(score));
}

#include "LevelManager.h"

void LevelManager::_register_methods()
{
	register_method("_ready", &LevelManager::_ready);
}

void LevelManager::_init()
{
}

void LevelManager::_ready()
{
}

void LevelManager::CompleteLevel(int id)
{
	cout << "level " << id << " completed" << endl;
}

void LevelManager::LoadLevel(int id)
{
	//call_deferred("DeferredLoadLevel", id);
	if(id==-1)
		get_tree()->change_scene(mainMenuPath);
	else
		get_tree()->change_scene(levelPath[id]);
}

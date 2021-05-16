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

void LevelManager::CompleteLevel(int completed, int opened)
{
	if(opened >= 0)
		DataLoader::GetSingleton()->SetLevelAvailable(opened, true);
}

void LevelManager::LoadLevel(int id)
{
	if(id==-1)
		get_tree()->change_scene(mainMenuPath);
	else
		get_tree()->change_scene(levelPath[id]);
}

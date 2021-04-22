#include "MenuSound.h"

void MenuSound::_register_methods()
{
	register_method("_ready", &MenuSound::_ready);
}

void MenuSound::_init()
{
}

void MenuSound::_ready()
{
	play();
}



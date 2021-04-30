#include "CommonLib.h"
#include "Player.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Menu_buttons.h"
#include "MenuSound.h"
#include "Robat.h"
#include "PauseScreen.h"
#include "ResumeButton.h"
#include "LevelEnd.h"
#include "LevelManager.h"
#include "Platform.h"
#include "Counter.h"
#include "InterfaceManager.h"


extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	Godot::nativescript_init(handle);

	register_class<Player>();
	register_class<Bullet>();
	register_class<BulletManager>();
	register_class<Menu_buttons>();
	register_class<MenuSound>();
	register_class<Robat>();
	register_class<PauseScreen>();
	register_class<ResumeButton>();
	register_class<LevelEnd>();
	register_class<LevelManager>();
	register_class<Platform>();
	register_class<Counter>();
	register_class<InterfaceManager>();
}
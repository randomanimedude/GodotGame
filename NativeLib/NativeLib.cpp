#include "Player.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Menu_buttons.h"
#include "MenuSound.h"
#include "Robat.h"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
	godot::Godot::nativescript_init(handle);

	godot::register_class<Player>();
	godot::register_class<Bullet>();
	godot::register_class<BulletManager>();
	godot::register_class<Menu_buttons>();
	godot::register_class<MenuSound>();
	godot::register_class<Robat>();
}

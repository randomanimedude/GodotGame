#pragma once

#include "CommonLib.h"
#include <Control.hpp>
#include <InputEvent.hpp>
#include <SceneTree.hpp>

class PauseScreen :
    public Control
{
	//godot structure
	GODOT_CLASS(PauseScreen, Control);
	 
	static inline PauseScreen* instance;

public:
	static void _register_methods();
	void _init();

	void _input(InputEvent* e);
	void Pause();

	static PauseScreen* getInstance();
};


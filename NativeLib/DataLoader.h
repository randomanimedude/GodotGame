#pragma once
#include "CommonLib.h"
#include <Node.hpp>
#include <File.hpp>
#include <JSON.hpp>
#include <JSONParseResult.hpp>
#include <Dictionary.hpp>
#include <Variant.hpp>
#include <AudioServer.hpp>

class DataLoader : public Node
{
	GODOT_CLASS(DataLoader, Node);

public:
	static void _register_methods();
	void _init();

	void _ready();
	static DataLoader* GetSingleton();

	void LoadLevelData();
	void SaveLevelData();
	void LoadSettingsData();
	void SaveSettingsData();
	void SetLevelAvailable(int index, bool status);
	bool GetLevelAvailable(int index);
	void ResetLevelAvailability();

private:
	static inline DataLoader* instance;
	
	AudioServer* audioServer = AudioServer::get_singleton();
	const String ProgressFile = "user://progress.save";
	const String SettingsFile = "user://settings.save";
	String buses[3] = { "Master", "Music", "SFX" };

	int numberOfLevels = 10;
	bool LevelAvailability[10];
};


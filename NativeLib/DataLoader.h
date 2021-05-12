#pragma once
#include "CommonLib.h"
#include <Node.hpp>
#include <File.hpp>
#include <JSON.hpp>
#include <JSONParseResult.hpp>
#include <Dictionary.hpp>
#include <Variant.hpp>

class DataLoader : public Node
{
	GODOT_CLASS(DataLoader, Node);

public:
	static void _register_methods();
	void _init();

	void _ready();
	static DataLoader* GetSingletone();

	void Load();
	void Save();
	void SetLevelComplitionStatus(int index, bool status);
	bool GetLevelComplitionStatus(int index);

private:
	static inline DataLoader* instance;

	const String ProgressFile = "user://progress.save";
	const String SettingsFile = "user://settings.save";

	int numberOfLevels = 11;
	bool LevelAvailability[11];
};


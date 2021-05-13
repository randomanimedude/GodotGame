#include "DataLoader.h"

void DataLoader::_register_methods()
{
	register_method("_ready", &DataLoader::_ready);
}

void DataLoader::_init()
{
	instance = this;

	Ref<File> file = File::_new();
	if (file->file_exists(ProgressFile))
		LoadLevelData();
	else
		ResetLevelAvailability();
}

void DataLoader::_ready()
{
}

DataLoader* DataLoader::GetSingletone()
{
	return instance;
}

void DataLoader::LoadLevelData()
{
	Ref<File> file = File::_new();
	if (file->file_exists(ProgressFile))
	{
		file->open(ProgressFile, file->READ);
		//load and parse json string
		Dictionary rez = JSON::get_singleton()->parse(file->get_as_text())->get_result();
		for (int i = 0; i < numberOfLevels; ++i)
			LevelAvailability[i] = rez[(String)"Level#" + String::num_int64(i)];
	}
}

void DataLoader::SaveLevelData()
{
	Ref<File> file = File::_new();
	file->open(ProgressFile, file->WRITE);

	//create dictionary with data and save it as json
	Dictionary dict;
	for (int i = 0; i < numberOfLevels; ++i)
		dict[(String)"Level#" + String::num_int64(i)] = LevelAvailability[i];
	file->store_string(dict.to_json());
	file->close();
}

void DataLoader::SetLevelAvailable(int index, bool status)
{
	if (index >= 0 && index < numberOfLevels)
		LevelAvailability[index] = status;
	SaveLevelData();
}

bool DataLoader::GetLevelAvailable(int index)
{
	if (index >= 0 && index < numberOfLevels)
		return LevelAvailability[index];
	else return false;
}

 void DataLoader::ResetLevelAvailability()
{
	 for (bool& status : LevelAvailability)
		 status = false;
	 LevelAvailability[0] = true;
}

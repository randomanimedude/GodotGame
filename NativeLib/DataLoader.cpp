#include "DataLoader.h"

void DataLoader::_register_methods()
{
	register_method("_ready", &DataLoader::_ready);
}

void DataLoader::_init()
{
	instance = this;
	for(bool &status: LevelAvailability)
		status = false;
	LevelAvailability[0] = true;
}

void DataLoader::_ready()
{
	Save();
	Load();
}

DataLoader* DataLoader::GetSingletone()
{
	return instance;
}

void DataLoader::Load()
{
	
}

void DataLoader::Save()
{
	File file;
	file.open(ProgressFile, File::ModeFlags::WRITE);
	//Dictionary dict;
	//dict.make<String, bool[]>("lvls", LevelAvailability);
	//file.store_string(dict.to_json());
	file.close();
	//file.open(ProgressFile, File::ModeFlags::READ);
	//
	//Dictionary rez = JSON::get_singleton()->parse(file.get_as_text())->get_result();
	//bool i[11] = { (bool)rez["lvls"] };
	//cout << i[0] << endl << i[1] << endl;
}

void DataLoader::SetLevelComplitionStatus(int index, bool status)
{
	if (index >= 0 && index < numberOfLevels)
		LevelAvailability[index] = status;
}

bool DataLoader::GetLevelComplitionStatus(int index)
{
	if (index >= 0 && index < numberOfLevels)
		return LevelAvailability[index];
}

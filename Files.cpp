#include "Files.h"
json Files::configJson = json();
std::mutex Files::mutex;
json Files::GetConfig()
{

	std::lock_guard<std::mutex> lock(mutex);
	if (configJson.empty())
	{
		ifstream ifs("MyJson.json");
		if (!ifs.is_open())
		{
			throw "Failed to open file.";
		}
		string content((istreambuf_iterator<char>(ifs)),
			(istreambuf_iterator<char>()));
		configJson = json::parse(content);
		ifs.close();
	}
	return configJson;
}
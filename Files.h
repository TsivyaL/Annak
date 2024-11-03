
#pragma once
#include "json.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <mutex>

using json = nlohmann::json;
using namespace std;

class Files
{
private:
	static json configJson;
	static std::mutex mutex;
	Files(); // המתכנן הפרטי למניעת יצירת עותקים
	Files(const Files&) = delete; // מונע העתקה
	Files& operator=(const Files&) = delete; // מונע העתקה

public:
	static json GetConfig();

};


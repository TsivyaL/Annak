
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
	Files(); // ������ ����� ������ ����� ������
	Files(const Files&) = delete; // ���� �����
	Files& operator=(const Files&) = delete; // ���� �����

public:
	static json GetConfig();

};


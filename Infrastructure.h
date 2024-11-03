#ifndef WORLD_H
#define WORLD_H

#pragma once
#include <vector>
#include "json.hpp"
#include "Files.h"
#include <string>
using namespace std;
using json = nlohmann::json;
class Infrastructure
{
	vector<int> capacity = vector<int>(5, 0);
	json config;
	bool complete;
	string type;
public:
	Infrastructure(string, vector<int>capacity = { 0,0,0,0,0 });
	bool IsComplete();
	void addResource(int, int);
	string GetType();
	void SetComplete();
	void MakeEmpty();
	int GetPeople();
	vector<int> GetCapacity();
};
#endif
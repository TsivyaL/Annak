#pragma once
#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H

#include <vector>
#include <string>
#include "json.hpp"
#include <fstream>
#include "Files.h"
#include "Square.h"
#include "Mover.h"

using json = nlohmann::json;
using namespace std;
class World
{
	std::vector<std::vector<Square>>world;
	json configurationJson;
	int rain;
	int cntCities;
	int cntVilages;
	int cntRoads;

public:
	World(const vector<vector<string>>&);
	vector<vector<Square>>& GetWorld();
	void addRain(int rain);
	int getRain();
	bool BuildInfrastructure(string, int, int);
	bool BuildMover(string, int, int, shared_ptr<Mover>newMoverPtr = nullptr);
	void DeleteMover(string type, int x, int y);
	bool IsRoadForCityOrVillage(string, int, int);
	int GetCntCities();
	void AddCity();
	int GetCntVilages();
	void AddVilage();
	int GetCntRoad();
	void AddRoad();
};
#endif


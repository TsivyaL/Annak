#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include <fstream>
#include<iostream>
#include "Files.h"
using json = nlohmann::json;
using namespace std;
class Tile {
	string numTile;
	string TileName;
	vector<double> resource;
	string findTile(int tileNum);
	json configurationJson;
	//int rain;
public:
	vector<double> getResource();
	string getNumTile();
	string getTileName();
	Tile(string, const vector<double>& resource = vector<double>(4, 0));
	void AddResource(double, string);
	friend ostream& operator<<(ostream& os, Tile& ti) {
		for (int resource : ti.resource)
			os << (int)resource << " ";
		return os;
	}
};
#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "json.hpp"
#include "Files.h"
#include "Tile.h"
#include "Infrastructure.h"
#include "Mover.h"
using json = nlohmann::json;
using namespace std;
class Square {
	shared_ptr<Tile> currentTile;
	shared_ptr<Infrastructure> currentInfrastructure;
	shared_ptr<Mover>currentMover;
	json configurationJson;
public:
	Square(shared_ptr<Tile>);
	Square(const string&);
	Square();
	void AddResourceToTileSquare(double, string);
	string GetTileName();
	shared_ptr<Tile> GetCurrentTile();
	void SetcurrentTile(string);
	void SetcurrentTile(shared_ptr<Tile>);
	void SetcurrentMover(shared_ptr<Mover>);
	void SetCurrentInfrastructure(string);
	void SetCurrentInfrastructure(shared_ptr<Infrastructure>);
	shared_ptr<Infrastructure> GetCurrentInfrastructure();
	shared_ptr<Mover> GetCurrentMover();
	void AddResourceToMover();
	void SetcurrentMover(string);
	friend ostream& operator<<(ostream& os, Square& sq) {
		for (int resourceS : sq.GetCurrentTile()->getResource())
			os << (int)resourceS << " ";
		return os;
	}

};
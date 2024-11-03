#pragma once
#include <vector>
#include <string>
#include "Files.h"
using namespace std;
class Mover
{

private:
	vector<int> resource;
	string type;
public:
	Mover(string, vector<int>capacity = { 0,0,0,0,0 });
	void TakeResources();
	string GetType();
	//virtual void Move() = 0;
	void MakeEmpty();
	vector<int> GetResorces();
	void AddResource(int, int);


};


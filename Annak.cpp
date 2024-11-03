#include <iostream>
#include "Command.h"
#include "Input.h"
#include "json.hpp"
#include "Utility.h"
#include <fstream>
#include <string>
#include "World.h"
#include "Files.h"
using namespace std;
using json = nlohmann::json;
void AddInfracture(string type, World& iWorld);
void actWait(World& iWorld, int wait);
void acts(int* s1, int* s2, Input& i, World& iWorld)
{
	for (shared_ptr<Command> step : i.steps)
	{
		if (step->name == "TakeResources") {
			iWorld.BuildMover(iWorld.GetWorld()[(*s2) - 1][(*s1) - 1].GetCurrentMover()->GetType(),
				stoi(step->arguments[1]), stoi(step->arguments[0]), iWorld.GetWorld()[(*s2) - 1][(*s1) - 1].GetCurrentMover());

			iWorld.DeleteMover(iWorld.GetWorld()[(*s2) - 1][(*s1) - 1].GetCurrentMover()->GetType(), (*s2),(*s1));
			iWorld.GetWorld()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].AddResourceToMover();
		}
		else if (step->name == "People"){
			if (iWorld.GetWorld()[stoi(step->arguments[2])-1][stoi(step->arguments[1])-1].GetCurrentInfrastructure() != nullptr)
				iWorld.GetWorld()[stoi(step->arguments[2])-1][stoi(step->arguments[1])-1].
				GetCurrentInfrastructure()->addResource(4, stoi(step->arguments[0]));
		}
		else if (step->name == "Select") {
			*s1 = stoi(step->arguments[0]);
			*s2 = stoi(step->arguments[1]);
		}
		else if (step->name == "Work") {

			if (iWorld.GetWorld()[(*s2) - 1][(*s1) - 1].GetCurrentInfrastructure() != nullptr)
			{
				iWorld.GetWorld()[(*s2) - 1][(*s1) - 1].GetCurrentInfrastructure()->addResource(4, -1);
				iWorld.GetWorld()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].SetcurrentMover("People");			}
			else {
				iWorld.GetWorld()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].SetcurrentMover(iWorld.GetWorld()[(*s2) - 1][(*s1) - 1].GetCurrentMover());
				iWorld.GetWorld()[(*s2) - 1][(*s1) - 1].SetcurrentMover((shared_ptr<Mover>)nullptr);
			}
			
			vector<double> res = iWorld.GetWorld()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].GetCurrentTile()->getResource();
			for (int i=0; i<res.size();i++ )
			{
				if (res[i] > 0)
				{
					iWorld.GetWorld()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].GetCurrentTile()->AddResource(-1,Files::GetConfig()["ResourceTypes"][i]);
					iWorld.GetWorld()[stoi(step->arguments[1]) - 1][stoi(step->arguments[0]) - 1].AddResourceToMover();
				}		
			}
		}
		else if (step->name == "Rain") {
			iWorld.addRain(stoi(step->arguments[0]));
		}
		else if (step->name == "Wait") {
			if (iWorld.getRain() < stoi(step->arguments[0])) {
				actWait(iWorld, iWorld.getRain());
				iWorld.addRain(-iWorld.getRain());
			}
			else {
				actWait(iWorld, stoi(step->arguments[0]));
				iWorld.addRain(-stoi(step->arguments[0]));
			}
		}
		else if (step->name == "Build") {
			if (iWorld.IsRoadForCityOrVillage(step->arguments[0], stoi(step->arguments[2]), stoi(step->arguments[1]))) {
				iWorld.BuildInfrastructure(step->arguments[0], stoi(step->arguments[2]), stoi(step->arguments[1]));
				AddInfracture(step->arguments[0], iWorld);
			}
			//if (iWorld.GetWorld()[stoi(step->arguments[2])][stoi(step->arguments[1])].GetCurrentInfrastructure() != nullptr &&
			//	iWorld.GetWorld()[stoi(step->arguments[2])][stoi(step->arguments[1])].GetCurrentInfrastructure()->IsComplete())

		}
		else if (step->name == "MakeEmpty") {
			if (iWorld.GetWorld()[stoi(step->arguments[1])][stoi(step->arguments[0])].GetCurrentInfrastructure() != nullptr)
				iWorld.GetWorld()[stoi(step->arguments[1])][stoi(step->arguments[0])].GetCurrentInfrastructure()->MakeEmpty();
		}

	}
}

void actWait(World& iWorld, int wait) {
	for (int i = 0; i < iWorld.GetWorld().size(); i += 5) {
		for (int j = 0; j < iWorld.GetWorld()[i].size(); j += 5) {
			int woodAmount = Files::GetConfig()["Rains"]["Wood"].get<int>();
			int woolAmount = Files::GetConfig()["Rains"]["Wool"].get<int>();
			if (iWorld.GetWorld()[i][j].GetCurrentTile()->getTileName() == "Forest")
			{
				double toAdd = (double)((double)wait / (double)woodAmount);
				iWorld.GetWorld()[i][j].GetCurrentTile()->AddResource(toAdd, "Wood");
			}
			if (iWorld.GetWorld()[i][j].GetCurrentTile()->getTileName() == "Field") 
			{
				double toAdd = (double)((double)wait / (double)woolAmount);
				iWorld.GetWorld()[i][j].GetCurrentTile()->AddResource(toAdd, "Wool");
			}
		}
	}
}
void start(Input& i, World& iWorld)
{
	int x;
	for (shared_ptr<Command> s : i.start)
	{
		json j = Files::GetConfig();
		if (s->name == "Resource")
		{
			iWorld.GetWorld()[stoi(s->arguments[3])-1][stoi(s->arguments[2])-1].AddResourceToTileSquare(stoi(s->arguments[0]), s->arguments[1]);
		}
		else if (s->name == "Build")
		{
			iWorld.BuildInfrastructure(s->arguments[0], stoi(s->arguments[2]), stoi(s->arguments[1]));
			if (iWorld.GetWorld()[stoi(s->arguments[2])][stoi(s->arguments[1])].GetCurrentInfrastructure() != nullptr) {
				iWorld.GetWorld()[stoi(s->arguments[2])][stoi(s->arguments[1])].GetCurrentInfrastructure()->SetComplete();
				AddInfracture(s->arguments[0], iWorld);
			}

		}
		else if (s->name == "MakeEmpty")
		{
			if (iWorld.GetWorld()[stoi(s->arguments[1])-1][stoi(s->arguments[0])-1].GetCurrentInfrastructure() != nullptr)
				iWorld.GetWorld()[stoi(s->arguments[1])-1][stoi(s->arguments[0])-1].GetCurrentInfrastructure()->MakeEmpty();
		}
		else if (s->name == "Manufacture") {
			if (iWorld.GetWorld()[stoi(s->arguments[2])-1][stoi(s->arguments[1])-1].GetCurrentMover() == nullptr) {
				iWorld.BuildMover(s->arguments[0], stoi(s->arguments[2]), stoi(s->arguments[1]));
			}
		}
		else if (s->name == "People") {
			if (iWorld.GetWorld()[stoi(s->arguments[2])-1][stoi(s->arguments[1])-1].GetCurrentInfrastructure() != nullptr) {
				iWorld.GetWorld()[stoi(s->arguments[2])-1][stoi(s->arguments[1])-1].GetCurrentInfrastructure()->addResource(4, stoi(s->arguments[0]));
			}
			else {
				iWorld.GetWorld()[stoi(s->arguments[2])-1][stoi(s->arguments[1])-1].SetcurrentMover("People");
			}

		}
	}
}
void AddInfracture(string type, World& iWorld) {
	if (type == "City") {
		iWorld.AddCity();
	}
	else if (type == "Village") {
		iWorld.AddVilage();
	}
	else
		iWorld.AddRoad();

}

void OutputAssert(int select1, int select2, Input& i, World& world) {
	for (size_t assert = 0; assert < i.asserts.size(); assert++)
	{
		if (i.asserts[assert] == "SelectedResource") {

			cout << i.asserts[assert] << " ";

			if (world.GetWorld()[select2 - 1][select1 - 1].GetCurrentInfrastructure() != nullptr) {
				for (int resourceS=0; resourceS < world.GetWorld()[select2 - 1][select1 - 1].GetCurrentInfrastructure()->GetCapacity().size()-1;resourceS++)
					cout << world.GetWorld()[select2 - 1][select1 - 1].GetCurrentInfrastructure()->GetCapacity()[resourceS] << " ";
			}
			else
				cout << world.GetWorld()[select2 - 1][select1 - 1] << "\n";
		}

		else if (i.asserts[assert] == "SelectedCategory") {
			if (world.GetWorld()[select2 - 1][select1 - 1].GetCurrentInfrastructure() != nullptr)
				cout << i.asserts[assert] << " " << world.GetWorld()[select2 - 1][select1 - 1].GetCurrentInfrastructure()->GetType() << "\n";
			else
				cout << i.asserts[assert] << " " << world.GetWorld()[select2 - 1][select1 - 1].GetTileName() << "\n";
		}

		else if (i.asserts[assert] == "SelectedComplete") {
			if (world.GetWorld()[select2 - 1][select1 - 1].GetCurrentInfrastructure() != nullptr)
			{
				cout << i.asserts[assert] << " ";
				world.GetWorld()[select2][select1].GetCurrentInfrastructure()->IsComplete() ? cout << "true\n" : cout << "false\n";
			}
			else {
				cout << i.asserts[assert] << " " << "false" << "\n";
			}
		}

		else if (i.asserts[assert] == "VillageCount") {
			cout << i.asserts[assert] << " " << world.GetCntVilages() << "\n";
		}

		else if (i.asserts[assert] == "CityCount") {
			cout << i.asserts[assert] << " " << world.GetCntCities() << "\n";
		}

		else if (i.asserts[assert] == "RoadCount") {
			cout << i.asserts[assert] << " " << world.GetCntRoad() << "\n";
		}

		else if (i.asserts[assert] == "SelectedPeople") {
			if (world.GetWorld()[select2][select1].GetCurrentInfrastructure() != nullptr) {
				cout << i.asserts[assert] << " " << world.GetWorld()[select2][select1].GetCurrentInfrastructure()->GetPeople() << "\n";
			}
		}

		else if (i.asserts[assert] == "SelectedCar") {
			if (world.GetWorld()[select2][select1].GetCurrentMover() != nullptr) {
				if (world.GetWorld()[select2][select1].GetCurrentMover()->GetType() == "Car")
					cout << i.asserts[assert] << " 1";
			}
			else
				cout << i.asserts[assert] << " 0";
		}

		else if (i.asserts[assert] == "SelectedTruck") {
			if (world.GetWorld()[select2][select1].GetCurrentMover() != nullptr) {
				if (world.GetWorld()[select2][select1].GetCurrentMover()->GetType() == "Truck")
					cout << i.asserts[assert] << " 1";
			}
			else
				cout << i.asserts[assert] << " 0";
		}

	}
}
int main()
{
	Input i;

	i.parse_and_store();
	World world((*i.world).data);
	start(i, world);
	int select1, select2;
	acts(&select1, &select2, i, world);
	OutputAssert(select1, select2, i, world);

}
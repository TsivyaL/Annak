#include "World.h"

World::World(const vector<vector<string>>& worldTiles) {

	this->configurationJson = Files::GetConfig();
	int tileWidthConfig = this->configurationJson["Sizes"]["Tile"][0].get<int>();
	int tileHeightConfig = this->configurationJson["Sizes"]["Tile"][1].get<int>();
	this->world = std::vector<std::vector<Square>>(worldTiles.size() * tileWidthConfig);
	this->cntCities = 0;
	this->cntRoads = 0;
	this->cntVilages = 0;

	for (size_t tileRowIndex = 0; tileRowIndex < worldTiles.size() * tileWidthConfig; tileRowIndex += tileWidthConfig) {
		for (size_t tileColumnIndex = 0; tileColumnIndex < tileWidthConfig; tileColumnIndex++) {
			this->world[tileColumnIndex + tileRowIndex] = vector<Square>(worldTiles[tileRowIndex / tileHeightConfig].size() * tileHeightConfig);
		}
	}

	for (size_t tileRowIndex = 0; tileRowIndex < worldTiles.size(); tileRowIndex++) {

		for (size_t tileColumnIndex = 0; tileColumnIndex < worldTiles[tileRowIndex].size(); tileColumnIndex++) {
			Square newTile(worldTiles[tileRowIndex][tileColumnIndex]);
			for (size_t i = 0; i < tileWidthConfig; i++)
			{
				for (size_t j = 0; j < tileHeightConfig; j++)
				{
					this->world[tileRowIndex * tileWidthConfig + i][tileColumnIndex * tileHeightConfig + j].SetcurrentTile(newTile.GetCurrentTile());
				}
			}

		}

	}
}
vector<vector<Square>>& World::GetWorld() {
	return this->world;
}
void World::addRain(int rain) {
	this->rain += rain;
}
int World::getRain() {
	return this->rain;
}
bool World::IsRoadForCityOrVillage(string type, int x, int y)
{
	bool isRoad = false;
	int infacWidthConfig = this->configurationJson["Sizes"][type][0].get<int>();
	int infactHeightConfig = this->configurationJson["Sizes"][type][1].get<int>();
	int roadSize = this->configurationJson["Sizes"]["Road"][1].get<int>();

	/*if (x >= 0 && x < this->GetWorld().size() &&  y>= 0 && y < this->GetWorld()[x].size())
	{
		for (int i = x; i < x + infacWidthConfig; i++)
		{
			if (y - 1 >= 0 && this->GetWorld()[i][y - 1].GetCurrentInfrastructure() != nullptr
				&& this->GetWorld()[i][y - 1].GetCurrentInfrastructure()->GetType() == "Road" &&
				i + roadSize - 1 < this->GetWorld()[x].size() &&
				this->GetWorld()[i + roadSize - 1][y - 1].GetCurrentInfrastructure() != nullptr &&
				this->GetWorld()[i + roadSize - 1][y - 1].GetCurrentInfrastructure()->GetType() == "Road")
			{
				return true;
			}
		}
	}*/

	/*if (y + infactHeightConfig < this->GetWorld().size() && x >= 0 && x < this->GetWorld()[y].size())
	{
		for (int i = x; i < x + infactHeightConfig - roadSize; i++)
		{
			if (this->GetWorld()[y + infactHeightConfig][i].GetCurrentInfrastructure() != nullptr &&
				this->GetWorld()[y + infactHeightConfig][i].GetCurrentInfrastructure()->GetType() == "Road" &&
				this->GetWorld()[y + infactHeightConfig][i + roadSize - 1].GetCurrentInfrastructure() != nullptr &&
				this->GetWorld()[y + infactHeightConfig][i + roadSize - 1].GetCurrentInfrastructure()->GetType() == "Road")
			{
				return true;
			}
		}
	}

	if (x + infactHeightConfig < this->GetWorld()[y].size() && y >= 0 && y < this->GetWorld().size())
	{
		for (int i = y; i < y + infactHeightConfig - roadSize; i++)
		{
			if (this->GetWorld()[i][x + infactHeightConfig].GetCurrentInfrastructure() != nullptr &&
				this->GetWorld()[i][x + infactHeightConfig].GetCurrentInfrastructure()->GetType() == "Road" &&
				this->GetWorld()[i + roadSize - 1][x + infactHeightConfig].GetCurrentInfrastructure() &&
				this->GetWorld()[i + roadSize - 1][x + infactHeightConfig].GetCurrentInfrastructure()->GetType() == "Road")
			{
				return true;
			}
		}
	}

	if (x > 0 && y >= 0 && y < this->GetWorld().size())
	{
		for (int i = y; i < y + infacWidthConfig - roadSize; i++)
		{
			if (this->GetWorld()[i][x - 1].GetCurrentInfrastructure() != nullptr &&
				this->GetWorld()[i][x - 1].GetCurrentInfrastructure()->GetType() == "Road" &&
				this->GetWorld()[i + roadSize - 1][x - 1].GetCurrentInfrastructure() != nullptr &&
				this->GetWorld()[i + roadSize - 1][x - 1].GetCurrentInfrastructure()->GetType() == "Road")
			{
				return true;
			}
		}
	}*/

	return true;
}
bool World::BuildInfrastructure(string type, int x, int y) {
	int infacWidthConfig = this->configurationJson["Sizes"][type][0].get<int>();
	int infactHeightConfig = this->configurationJson["Sizes"][type][1].get<int>();
	for (int Width = x - 1; Width < x - 1 + infacWidthConfig; Width++) {
		for (int height = y - 1; height < y - 1 + infactHeightConfig; height++) {
			if (Width >= world.size() || height >= world[Width].size() || Width < 0 || height < 0
				|| this->GetWorld()[Width][height].GetTileName() != "Ground"
				|| this->GetWorld()[Width][height].GetCurrentInfrastructure() != nullptr)
				return false;
		}
	}

	Infrastructure newInfact(type);
	shared_ptr<Infrastructure> ptrInfact = make_shared<Infrastructure>(newInfact);
	for (int Width = x - 1; Width < x - 1 + infacWidthConfig; Width++) {
		for (int height = y - 1; height < y - 1 + infactHeightConfig; height++) {
			this->GetWorld()[Width][height].SetCurrentInfrastructure(ptrInfact);
		}
	}
	return true;
}
bool World::BuildMover(string type, int x, int y, shared_ptr<Mover>newMoverPtr) {
	int moveWidthConfig = this->configurationJson["Sizes"][type][0].get<int>();
	int moveHeightConfig = this->configurationJson["Sizes"][type][1].get<int>();
	for (int Width = x - 1; Width < x - 1 + moveWidthConfig; Width++) {
		for (int height = y - 1; height < y - 1 + moveHeightConfig; height++) {
			if (Width >= world.size() || height >= world[Width].size() || Width < 0 || height < 0)
				return false;
		}
	}
	if (newMoverPtr == nullptr) {
		Mover newMover(type);
		newMoverPtr = make_shared<Mover>(newMover);
	}

	for (int Width = x - 1; Width < x - 1 + moveWidthConfig; Width++) {
		for (int height = y - 1; height < y - 1 + moveHeightConfig; height++) {
			this->GetWorld()[Width][height].SetcurrentMover(newMoverPtr);
		}
	}
	return true;
}

void World::DeleteMover(string type ,int x, int y) {
	int moveWidthConfig = this->configurationJson["Sizes"][type][0].get<int>();
	int moveHeightConfig = this->configurationJson["Sizes"][type][1].get<int>();
	for (int Width = x - 1; Width < x - 1 + moveWidthConfig; Width++) {
		for (int height = y - 1; height < y - 1 + moveHeightConfig; height++) {
			this->GetWorld()[Width][height].SetcurrentMover((shared_ptr<Mover>)nullptr);
		}
	}
}

int World::GetCntCities() {
	return this->cntCities;
}
void World::AddCity() {
	this->cntCities++;
}
int World::GetCntVilages() {
	return this->cntVilages;
}
void World::AddVilage() {
	this->cntVilages++;
}
int World::GetCntRoad() {
	return this->cntRoads;
}
void World::AddRoad() {
	this->cntRoads++;
}


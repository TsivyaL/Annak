#include "Tile.h"
Tile::Tile(string num, const vector<double>& resorce) {
    this->configurationJson = Files::GetConfig();
    this->numTile = num;
    this->TileName = this->findTile(stoi(num));
    this->resource = vector<double>(4, 0);
    for (size_t i = 0; i < resorce.size(); i++)
    {
        this->resource[i] = resorce[i];
    }
}

string Tile::getNumTile() {
    return this->numTile;
}
string Tile::getTileName() {
    return this->TileName;
}
string Tile::findTile(int tileNum) {

    for (auto a = this->configurationJson["Tiles"].begin(); a != this->configurationJson["Tiles"].end(); a++) {
        if (a.value() == tileNum)
        {
            return a.key();
        }
    }
    return "tile not found";
}
void Tile::AddResource(double amount, string resourceType) {

    int index = 0;
    for (string resourceS : this->configurationJson["ResourceTypes"]) {
        if (resourceS == resourceType) {
            this->resource[index] += amount;
            return;
        }
        index++;
    }
}
vector<double>Tile::getResource() {
    return this->resource;
}
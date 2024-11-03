#include "Square.h"

Square::Square(shared_ptr<Tile>samePtrTile) {
	this->currentTile = samePtrTile;
	this->currentInfrastructure = nullptr;
	this->configurationJson = Files::GetConfig();
}

Square::Square(const string& currentTile) {
	this->currentTile = make_shared<Tile>(currentTile);
	this->currentInfrastructure = nullptr;
	this->configurationJson = Files::GetConfig();
}

Square::Square() {
	this->currentTile = nullptr;
	this->currentInfrastructure = nullptr;
	this->configurationJson = Files::GetConfig();
}

shared_ptr<Tile> Square::GetCurrentTile() {
	return this->currentTile;
}

void Square::SetcurrentTile(string tile) {
	this->currentTile.reset(new Tile(tile));
}

void Square::SetcurrentTile(shared_ptr<Tile>sPtrTile) {
	this->currentTile = sPtrTile;
}

void Square::AddResourceToTileSquare(double amount, string resourceType) {
	if (this->currentMover != nullptr) {
		int index = 0;
		for (string resourceS : this->configurationJson["ResourceTypes"]) {
			if (resourceS == resourceType) {
				this->currentMover->AddResource(index, amount);
				return;
			}
			index++;
		}

	}
	else if (this->currentInfrastructure != nullptr) {
		int index = 0;
		for (string resourceS : this->configurationJson["ResourceTypes"]) {
			if (resourceS == resourceType) {
				this->currentInfrastructure->addResource(index, amount);
				return;
			}
			index++;
		}
		
	}
	else
		this->GetCurrentTile()->AddResource(amount, resourceType);

}

void Square::SetCurrentInfrastructure(string type) {

	this->currentInfrastructure.reset(new Infrastructure(type));
}

void Square::SetCurrentInfrastructure(shared_ptr<Infrastructure> sPtrInfrastructure) {
	this->currentInfrastructure = sPtrInfrastructure;
}

void Square::SetcurrentMover(shared_ptr<Mover>sPtrMover) {
	this->currentMover = sPtrMover;
}

string Square::GetTileName() {
	return this->GetCurrentTile()->getTileName();
}

shared_ptr<Infrastructure> Square::GetCurrentInfrastructure() {
	return this->currentInfrastructure;
}

shared_ptr<Mover>Square::GetCurrentMover() {
	return this->currentMover;
}

void Square::SetcurrentMover(string type) {
	this->currentMover.reset(new Mover(type));
}

void Square::AddResourceToMover() {
	if (this->currentMover != nullptr) {

		vector<int> capacity;
		capacity = Files::GetConfig()["Capacities"][this->currentMover->GetType()].get<vector<int>>();
		if (this->currentInfrastructure != nullptr) {
			for (size_t i = 0; i < capacity.size(); i++)
			{
				if (this->currentInfrastructure->GetCapacity()[i] - capacity[i] >= 0) {
					this->currentInfrastructure->addResource(i, -capacity[i]);
					this->currentMover->AddResource(i, capacity[i]);
				}
				else {
					this->currentMover->AddResource(i, this->currentInfrastructure->GetCapacity()[i]);
					this->currentInfrastructure->addResource(i,-this->currentInfrastructure->GetCapacity()[i]);
				}
			}
		}
		else {

			for (size_t i = 0; i < this->currentTile->getResource().size(); i++)
			{
				if (this->currentTile->getResource()[i] - capacity[i] >= 0) {
					this->currentTile->AddResource(-capacity[i], Files::GetConfig()["ResourceTypes"][i]);
					this->currentMover->AddResource(i, capacity[i]);

				}
				else {
					this->currentMover->AddResource(i, this->currentTile->getResource()[i]);
					this->currentTile->AddResource(-this->currentTile->getResource()[i], Files::GetConfig()["ResourceTypes"][i]);
				}

			}
		}
	}
	
}

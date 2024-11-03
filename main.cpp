#include <iostream>
#include "Command.h"
#include "Input.h"
#include "json.hpp"
#include "Utility.h"
#include <fstream>
#include <string>
#include "World.h"
using namespace std;
int main()
{
    Input i;
    i.parse_and_store();
    World world((*i.world).data);
    int place=world.foundPlace((*i.start[0]).arguments);
    cout << world.findTile(place);
    //cout << i.asserts[0] << " " << findTile(foundPlace(i));
}
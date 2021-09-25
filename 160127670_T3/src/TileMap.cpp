#include "../include/TileMap.hpp"
#include "../include/GameObject.hpp"
#include "../include/TileSet.hpp"
#include "../include/Component.hpp"

#include <fstream>
#include <sstream>

using namespace std;

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component(associated)
{

  this->Load(file);

  this->tileset = tileSet;
}

void TileMap::Load(string file)
{

  ifstream tileMap("./assets/map/tileMap.txt");

  if (tileMap.is_open())
  {
    string line;
    while (getline(tileMap, line))
    {
      
      istringstream ss(line);
      while(ss){
        string number;
        if(!getline(ss, number, ',')) break;
        cout << number << endl;
      }

    }
  }
  else
  {
    ofstream logfile("Errors.log");

    logfile << "TileMap cannot be read" << endl;
  }
}
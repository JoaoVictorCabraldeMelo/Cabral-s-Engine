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

void TileMap::Load(const string &file)
{

  fstream tileMap(file);

  if (tileMap.is_open())
  {
    string line;
    int count = 0;
    while (getline(tileMap, line))
    {

      stringstream numbers(line);
      while (numbers.good())
      {

        string number;
        getline(numbers, number, ',');

        if (count == 0 && number != "\r" && number != "\n")
        {
          this->mapWidth = stoi(number);
          getline(numbers, number, ',');
          this->mapHeight = stoi(number);
          getline(numbers, number, ',');
          this->mapDepth = stoi(number);
        }
        else if (number != "\r" && number != "\n")
        {
          this->tileMatrix.push_back(stoi(number) - 1);
        }
      }
      count++;
    }
  }
  else
  {
    ofstream logfile("Errors.log");

    logfile << "TileMap cannot be read" << endl;
  }
}

void TileMap::SetTileSet(TileSet *tileSet)
{
  this->tileset = tileSet;
}

int &TileMap::At(int x, int y, int z)
{
  int xCalculated = x * this->mapWidth;
  int zCalculated = (this->mapHeight * this->mapWidth) * z;

  return this->tileMatrix[xCalculated + zCalculated + y];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
  int tilesToRender = this->mapHeight * this->mapWidth;
  int beginRender = 0;

  beginRender = layer * tilesToRender;
  tilesToRender += beginRender;

  for (int i = beginRender; i < tilesToRender; i++)
  {
    this->tileset->RenderTile(this->tileMatrix[i], cameraX, cameraY);
  }
}

void TileMap::Render()
{

  for (int i = 0; i < this->mapDepth; i++)
  {
    this->RenderLayer(i);
  }
}

int TileMap::GetWidth()
{
  return this->mapWidth;
}

int TileMap::GetHeight()
{
  return this->mapHeight;
}

int TileMap::GetDepth()
{
  return this->mapDepth;
}

void TileMap::Update(float dt)
{
}

bool TileMap::Is(const string type)
{
  if (type == "Tilemap")
    return true;
  else
    return false;
}
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
  int zCalculated = this->mapHeight * this->mapWidth * z;
  int yCalculated = this->mapWidth * y;

  return this->tileMatrix[x + zCalculated + yCalculated];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
  for (int i = 0; i < this->mapHeight; i++) {
    for (int j = 0; j < this->mapWidth; j++)
    {
      int x = i * this->tileset->GetTileHeight() - cameraX;
      int y = j * this->tileset->GetTileWidth() - cameraY;

      this->tileset->RenderTile(this->At(i, j, layer), x, y);
    }
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
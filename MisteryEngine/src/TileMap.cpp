
#include "../include/TileMap.hpp"
#include "../include/GameObject.hpp"
#include "../include/TileSet.hpp"
#include "../include/Component.hpp"
#include "../include/Camera.hpp"

#include <fstream>
#include <sstream>

using namespace std;

TileMap::TileMap(GameObject &associated, const string& file, TileSet *tileSet) 
: Component(associated), tileset(tileSet)
{
  Load(file);
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
          mapWidth = stoi(number);
          getline(numbers, number, ',');
          mapHeight = stoi(number);
          getline(numbers, number, ',');
          mapDepth = stoi(number);
        }
        else if (number != "\r" && number != "\n")
        {
          tileMatrix.push_back(stoi(number)-1);
        }
      }
      count++;
    }
  }
  else
  {
    ofstream logfile("Errors.log", ofstream::app);

    logfile << "TileMap cannot be read" << endl;
  }
}

void TileMap::SetTileSet(TileSet *tileSet)
{
  tileset = tileSet;
}

int &TileMap::At(const int x, const int y, const int z)
{
  int zCalculated = mapHeight * mapWidth * z;
  int xCalculated = x;
  int yCalculated = mapWidth * y;

  return tileMatrix[xCalculated + zCalculated + yCalculated];
}

void TileMap::RenderLayer(const int layer, const int cameraX, const int cameraY) 
{

  int parallax_x = cameraX * (layer + 1);
  int parallax_y = cameraY * (layer + 1);

  for (int i = 0; i < mapWidth; i++)
  {
    for (int j = 0; j < mapHeight; j++)
    {
      int x = i * tileset->GetTileWidth() - parallax_x;
      int y = j * tileset->GetTileHeight() - parallax_y;

      tileset->RenderTile(At(i, j, layer), x, y);
    }
  }
}

void TileMap::Render()
{

  for (int i = 0; i < mapDepth; i++)
  {
    RenderLayer(i, Camera::pos.x, Camera::pos.y);
  }
}

int TileMap::GetWidth() const
{
  return mapWidth;
}

int TileMap::GetHeight() const
{
  return mapHeight;
}

int TileMap::GetDepth() const
{
  return mapDepth;
}

void TileMap::Update(float dt)
{
}

bool TileMap::Is(const string& type)
{
  if (type == "Tilemap")
    return true;
  else
    return false;
}
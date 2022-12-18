#include "../include/TileSet.hpp"
#include "../include/State.hpp"

#include <fstream>
#include <iostream>

using namespace std;

TileSet::TileSet(int tileWidth, int tileHeight, string file)
{

  GameObject *object = new GameObject();

  Sprite *tileSet = new Sprite(*object);

  this->tileSet = tileSet;

  this->tileSet->Open(file);

  this->rows = this->tileSet->GetHeight() / tileHeight;

  this->columns = this->tileSet->GetWidth() / tileWidth;

  this->tileHeight = tileHeight;

  this->tileWidth = tileWidth;
}

void TileSet::RenderTile(int index, float x, float y)
{
  
  if (index <= ((rows * columns) - 1) && index >= 0)
  {
    int xFor = (index % this->columns) * this->tileWidth;
    int yFor = (index / this->columns) * this->tileHeight;
    this->tileSet->SetClip(xFor, yFor, this->tileWidth, this->tileHeight);
    this->tileSet->Render(x, y,64,64);
    return;
  }

  ofstream logfile("Errors.log", ofstream::app);
  logfile << "Index: "<< index << " out of TileSet" << endl;


}

int TileSet::GetTileWidth()
{
  return this->tileWidth;
}

int TileSet::GetTileHeight()
{
  return this->tileHeight;
}

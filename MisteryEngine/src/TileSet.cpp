#include "../include/TileSet.hpp"
#include "../include/State.hpp"

#include <fstream>
#include <iostream>

using namespace std;

TileSet::TileSet(const int tileWidth, const int tileHeight, const string &file)
    : tileWidth(tileWidth), tileHeight(tileHeight)
{

  GameObject *object = new GameObject();

  Sprite *tileSet = new Sprite(*object);

  this->tileSet = tileSet;

  this->tileSet->Open(file);

  rows = tileSet->GetHeight() / tileHeight;

  columns = tileSet->GetWidth() / tileWidth;

}

void TileSet::RenderTile(const int index, const float x, const float y)
{
  if (index <= ((rows * columns) - 1) && index >= 0)
  {
    int xFor = (index % columns) * tileWidth;
    int yFor = (index / columns) * tileHeight;
    tileSet->SetClip(xFor, yFor, tileWidth, tileHeight);
    tileSet->Render(x, y,64,64);
    return;
  }
}

int TileSet::GetTileWidth() const
{
  return tileWidth;
}

int TileSet::GetTileHeight() const
{
  return tileHeight;
}

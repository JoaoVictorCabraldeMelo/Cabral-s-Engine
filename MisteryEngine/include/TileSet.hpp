#ifndef TILESET_H 
#define TILESET_H

#include "Sprite.hpp"



class TileSet
{
private:
  
  Sprite *tileSet;
  
  int rows;

  int columns;

  int tileWidth;

  int tileHeight;

public:
  TileSet(const int tileWidth, const int tileHeight, const std::string& file);

  void RenderTile(const int index, const float x, const float y);

  int GetTileWidth() const;

  int GetTileHeight() const;

};


#endif
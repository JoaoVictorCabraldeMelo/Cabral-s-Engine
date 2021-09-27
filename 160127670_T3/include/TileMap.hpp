#ifndef TILE_MAP_H
#define TILE_MAP_H 

#include "Component.hpp"
#include "TileSet.hpp"

class TileMap : public Component
{
private:
  std::vector<int> tileMatrix;

  TileSet *tileset;

  int mapWidth;

  int mapHeight;

  int mapDepth;

public:

  TileMap(GameObject &associated, std::string file, TileSet *tileSet);

  void Load(const std::string &file);

  void SetTileSet(TileSet *TileSet);

  int& At(int x, int y, int z = 0);

  void Render() override;

  void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

  int GetWidth();

  int GetHeight();

  int GetDepth();

  void Update(float dt) override;

  bool Is(std::string  type) override;
};


#endif
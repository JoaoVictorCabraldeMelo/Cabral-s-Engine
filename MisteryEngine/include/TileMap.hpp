#ifndef TILE_MAP_H
#define TILE_MAP_H 

#include "Component.hpp"
#include "TileSet.hpp"

class TileMap : public Component
{
public:

  TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);

  void Load(const std::string &file);

  void SetTileSet(TileSet* TileSet);

  int& At(const int x, const int y, const int z = 0);

  void Render() override;

  void RenderLayer(const int layer, const int cameraX = 0, const int cameraY = 0);

  int GetWidth() const;

  int GetHeight() const;

  int GetDepth() const;

  void Update(float dt) override;

  bool Is(const std::string&  type) override;

private:
  std::vector<int> tileMatrix;

  TileSet *tileset;

  int mapWidth;

  int mapHeight;

  int mapDepth;
};


#endif
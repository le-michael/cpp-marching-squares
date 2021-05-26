#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include <array>
#include <vector>

class Grid {
public:
  std::vector<std::vector<int>> anchors;

  Grid(int width, int height, int resolution);

  void setAnchorValues(sf::Vector2<int> pos, float radius, int value);

  void update(float dt);
  void draw(sf::RenderTarget &target);

private:
  int width, height;
  std::vector<std::vector<Cell>> cells;
  std::vector<sf::VertexArray> meshes;

  int cellState(int a, int b, int c, int d);
  void updateCellStates();
  sf::VertexArray createMesh(std::vector<sf::Vector2f> vertices);
};

#endif /* GRID_H */

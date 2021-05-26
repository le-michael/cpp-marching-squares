#include "grid.h"

// TODO: Swap resolution out with cell size to support non-square dimensions.
Grid::Grid(int width, int height, int resolution)
    : width(width), height(height) {
  cells =
      std::vector<std::vector<Cell>>(resolution, std::vector<Cell>(resolution));
  anchors = std::vector<std::vector<int>>(resolution + 1,
                                          std::vector<int>(resolution + 1, 0));

  float dx = static_cast<float>(width) / static_cast<float>(resolution);
  float dy = static_cast<float>(height) / static_cast<float>(resolution);

  for (int i = 0; i < resolution; ++i) {
    for (int j = 0; j < resolution; ++j) {
      cells[i][j].setPosition({i * dx, j * dy});
      cells[i][j].setSize({dx, dy});
    }
  }

  // tl----tc----tr
  // |            |
  // |            |
  // ml          mr
  // |            |
  // |            |
  // bl----bc----br
  auto tl = sf::Vector2f(0, 0);
  auto tc = sf::Vector2f(0.5, 0);
  auto tr = sf::Vector2f(1, 0);

  auto ml = sf::Vector2f(0, 0.5);
  auto mr = sf::Vector2f(1, 0.5);

  auto bl = sf::Vector2f(0, 1);
  auto bc = sf::Vector2f(0.5, 1);
  auto br = sf::Vector2f(1, 1);

  auto mesh0 = createMesh({});
  meshes.push_back(mesh0);

  auto mesh1 = createMesh({ml, bc, bl});
  meshes.push_back(mesh1);

  auto mesh2 = createMesh({mr, br, bc});
  meshes.push_back(mesh2);

  auto mesh3 = createMesh({ml, mr, bl, mr, br, bl});
  meshes.push_back(mesh3);

  auto mesh4 = createMesh({tc, tr, mr});
  meshes.push_back(mesh4);

  auto mesh5 = createMesh({ml, tc, bl, bl, tc, tr, tr, bc, bl, bc, tr, mr});
  meshes.push_back(mesh5);

  auto mesh6 = createMesh({tr, br, bc, bc, tc, tr});
  meshes.push_back(mesh6);

  auto mesh7 = createMesh({tc, tr, br, tc, br, bc, tc, bc, bl, tc, bl, ml});
  meshes.push_back(mesh7);

  auto mesh8 = createMesh({tl, tc, ml});
  meshes.push_back(mesh8);

  auto mesh9 = createMesh({tl, bc, bl, tl, tc, bc});
  meshes.push_back(mesh9);

  auto mesh10 = createMesh({ml, tl, bc, tl, br, bc, tl, mr, br, tl, tc, mr});
  meshes.push_back(mesh10);

  auto mesh11 = createMesh({tl, bc, bl, tl, tc, bc, tc, br, bc, tc, mr, br});
  meshes.push_back(mesh11);

  auto mesh12 = createMesh({tl, mr, ml, tl, tr, mr});
  meshes.push_back(mesh12);

  auto mesh13 = createMesh({tl, bc, bl, tl, tc, bc, tc, mr, bc, tc, tr, mr});
  meshes.push_back(mesh13);

  auto mesh14 = createMesh({tc, tr, br, tc, br, bc, tc, bc, ml, tc, ml, tl});
  meshes.push_back(mesh14);

  auto mesh15 = createMesh({tl, br, bl, tl, tr, br});
  meshes.push_back(mesh15);
}

void Grid::setAnchorValues(sf::Vector2<int> pos, float radius, int value) {
  float dx = width / cells.size();
  float dy = height / cells.size();

  for (int i = 0; i < anchors.size(); ++i) {
    for (int j = 0; j < anchors[0].size(); ++j) {
      float x = pos.x - i * dx;
      float y = pos.y - j * dy;
      if (radius * radius >= x * x + y * y) {
        anchors[i][j] = value;
      }
    }
  }
}

sf::VertexArray Grid::createMesh(std::vector<sf::Vector2f> vertices) {
  sf::VertexArray mesh(sf::LineStrip, vertices.size());

  for (int i = 0; i < vertices.size(); ++i) {
    mesh[i].position = vertices[i];
    mesh[i].color = sf::Color(0x201246ff);
  }

  return mesh;
}

int Grid::cellState(int a, int b, int c, int d) {
  return a * 8 + b * 4 + c * 2 + d * 1;
}

void Grid::updateCellStates() {
  for (int i = 0; i < cells.size(); ++i) {
    for (int j = 0; j < cells[i].size(); ++j) {
      int a = anchors[i][j];
      int b = anchors[i + 1][j];
      int c = anchors[i + 1][j + 1];
      int d = anchors[i][j + 1];
      int state = cellState(a, b, c, d);

      cells[i][j].mesh = meshes[state];
    }
  }
}

void Grid::update(float dt) { updateCellStates(); }

void Grid::draw(sf::RenderTarget &target) {
  for (auto row : cells) {
    for (auto cell : row) {
      cell.draw(target);
    }
  }
}

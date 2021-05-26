#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell {
public:
  sf::RectangleShape debugSprite;
  sf::VertexArray mesh;
  sf::Transform transform;

  sf::Vector2f pos;
  sf::Vector2f size;

  Cell();

  void setPosition(sf::Vector2f positon);
  void setSize(sf::Vector2f size);

  void draw(sf::RenderTarget &target);

private:
};

#endif /* CELL_H */

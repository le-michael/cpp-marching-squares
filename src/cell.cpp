#include "cell.h"
#include <array>
#include <iostream>

Cell::Cell() : pos({0, 0}), size({1, 1}) {
  debugSprite.setFillColor(sf::Color::Transparent);
  debugSprite.setOutlineColor(sf::Color::Green);
  debugSprite.setOutlineThickness(1);
}

void Cell::setPosition(sf::Vector2f pos) {
  this->pos = pos;
  transform.translate(pos);
  debugSprite.setPosition(pos);
}

void Cell::setSize(sf::Vector2f size) {
  this->size = size;
  transform.scale(size);
  debugSprite.setSize(size);
}

void Cell::draw(sf::RenderTarget &target) {
  // target.draw(debugSprite);
  target.draw(mesh, transform);
}

#include "grid.h"
#include "noise.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>

const int screenWidth = 800;
const int screenHeight = 800;
const int resolution = 100;

int main() {

  Grid grid(screenWidth, screenHeight, resolution);

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  Noise noise(seed);

  float step = 0.05;
  for (int i = 0; i <= resolution; ++i) {
    for (int j = 0; j <= resolution; ++j) {
      grid.anchors[i][j] = ceil(noise.noise(i * step, j * step, 0));
    }
  }

  sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight),
                          "Marching Squares",
                          sf::Style::Titlebar | sf::Style::Close);

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    auto pos = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      grid.setAnchorValues(pos, 25, 1);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      grid.setAnchorValues(pos, 50, 0);
    }

    grid.update(clock.restart().asSeconds());

    window.clear(sf::Color(0x8aa2ffff));
    grid.draw(window);
    window.display();
  }

  return 0;
}

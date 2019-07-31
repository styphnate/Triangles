#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define WIDTH 1000
#define HEIGHT 1000

int main() {
  constexpr static size_t clickCircleRadius = 2;

  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Triangles");
  window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - WIDTH / 2,
                                  sf::VideoMode::getDesktopMode().height / 2 - HEIGHT / 2));
  window.setFramerateLimit(60);

  std::vector<sf::CircleShape> clickCircles;
  std::vector<sf::VertexArray> triangles;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f mousePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
          sf::CircleShape tmpCircle(clickCircleRadius);
          tmpCircle.setPosition(mousePosition.x - clickCircleRadius, mousePosition.y - clickCircleRadius);
          tmpCircle.setFillColor(sf::Color::Red);
          clickCircles.push_back(tmpCircle);
        }
        if (clickCircles.size() == 3 ||
            (clickCircles.size() >= 3 && (clickCircles.size() % 2 == 0) && clickCircles.size() != 0)) {
          sf::VertexArray triangle(sf::Triangles, 3);
          triangle[0].position = sf::Vector2f(clickCircles.at(clickCircles.size() - 1).getPosition().x,
                                              clickCircles.at(clickCircles.size() - 1).getPosition().y);
          triangle[1].position = sf::Vector2f(clickCircles.at(clickCircles.size() - 2).getPosition().x,
                                              clickCircles.at(clickCircles.size() - 2).getPosition().y);
          triangle[2].position = sf::Vector2f(clickCircles.at(clickCircles.size() - 3).getPosition().x,
                                              clickCircles.at(clickCircles.size() - 3).getPosition().y);
          triangles.push_back(triangle);
        }
      }
    }
    window.clear();

    for (auto &circle : clickCircles) {
      window.draw(circle);
    }
    for (auto &triangle : triangles) {
      window.draw(triangle);
    }
    window.display();
  }

  return 0;
}
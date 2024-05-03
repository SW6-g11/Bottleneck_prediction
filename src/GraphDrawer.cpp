#include "GraphDrawer.h"
#include "paths.h"
#include "router.h"
#include "link.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void GraphDrawer::drawEdge(int start, int end, int weight) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(start * 100, 100), sf::Color::Black),
        sf::Vertex(sf::Vector2f(end * 100, 100), sf::Color::Black)
    };

    window.draw(line, 2, sf::Lines);

    // Display weight
    sf::Text text(std::to_string(weight), sf::Font(), 20);
    text.setPosition((start * 100 + end * 100) / 2 - 10, 90);
    window.draw(text);
}


void GraphDrawer::drawGraph() {
    window.clear(sf::Color::White);

    for (const auto& edge : edges) {
        drawEdge(edge.start, edge.end, edge.weight);
    }

    window.display();

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}

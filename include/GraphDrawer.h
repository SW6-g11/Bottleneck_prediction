#ifndef GRAPHDRAWER_H
#define GRAPHDRAWER_H
#include <string>
using namespace std;
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class GraphDrawer {
public:
    GraphDrawer(int numVertices, const std::vector<Edge>& edges);

    void drawGraph();
    

    GraphDrawer(int numVertices, const std::vector<Edge>& edges): numVertices(numVertices), edges(edges), window(sf::VideoMode(800, 600), "Weighted Graph") {}


private:
    int numVertices;
    std::vector<Edge> edges;
    sf::RenderWindow window;

    void drawEdge(int start, int end, int weight);



};



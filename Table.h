#pragma once
#include "SFML/Graphics.hpp"
#include "RoundedRectangle.h"
#include "TextBox.h"
#include <vector>
#include <string>

class Table {
public:
    Table(sf::Vector2f size, sf::Vector2f pos, sf::Color Frame, sf::Color Cin,
          float FrameThickness, float radius, sf::Vector2f CellSZ, sf::Font& f);
    ~Table() = default;
    void Draw(sf::RenderWindow& wnd);
    bool isMouseOver(sf::RenderWindow& window);
    void Scroll(std::pair<int, int> a);
    std::vector<std::string> get_data();
    std::string getCell(int i);
    void SetSize(sf::Vector2f size);
    void SetPosition(sf::Vector2f position);
    void SetGata(std::vector<std::string>& data_);
private:
    std::vector<int> fill;
    float maxSize;
    sf::Font font;
    sf::Color Bad_color;
    float ft;
    sf::Vector2f position;
    std::vector<std::string> data;
    sf::Vector2f CellSize;
    sf::Vector2f Start;
    RoundedRectangle out;
    RoundedRectangle in;
};
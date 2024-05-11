#pragma once
#include "SFML/Graphics.hpp"
#include "RoundedRectangle.h"
#include <string>
#include "iostream"

class TextBox {
public:
    TextBox(sf::Vector2f size, sf::Vector2f pos, sf::Color color, sf::Color pressed, sf::Font& font, std::string title, float radius);
    ~TextBox() = default;
    void SetPressed();
    void SetSimple();
    int getColor();
    void SetSize(sf::Vector2f size);
    void SetPosition(sf::Vector2f pos);
    void AddSimbol(char a);
    void RemoveSimbol();
    bool isMousOver(sf::RenderWindow& wnd);
    void Draw(sf::RenderWindow& wnd);
    void Clear();
    void SetText(std::string& str);
    std::string get_text();
private:
    bool is_title = true;
    float radius_;
    sf::Vector2f position;
    int start = 0;
    int TextBoxWidth;
    int TextBoxHeight;
    RoundedRectangle back;
    std::string data_;
    sf::Text text_;
    sf::Text title;

    sf::Font font_;

    sf::Color color_;
    sf::Color pressed_;
};

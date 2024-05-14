#pragma once
#include "Singleton.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowStyle.hpp>
class Screen : public Singleton<Screen> {
public:
    sf::RenderWindow* window;
    void Init () {
        window = new sf::RenderWindow(sf::VideoMode(1200, 1200), "Forest");
    }
    ~Screen() {
        delete window;
    }
};
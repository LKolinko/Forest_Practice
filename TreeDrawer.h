#pragma once
#include "iostream"
#include "random"
#include "vector"
#include "chrono"
#include "SFML/Graphics.hpp"
#include "Screen.h"
#include "RoundedRectangle.h"
#include "Button.h"
#include "queue"

class TreeDrawer {
public:
    TreeDrawer() = default;
    TreeDrawer(sf::Vector2u size_, sf::Vector2f pos_, std::string title, sf::Vector2f full_p, sf::Vector2u full_s);
    struct Node {
        Node(int64_t v);

        friend class TreesDrawer;
        virtual Node *GetLeft() const = 0;
        virtual Node *GetRight() const = 0;
        virtual std::string GetData() const = 0;
        int64_t val, size;
        bool isLeft = false;
        sf::Color color = sf::Color::Black;
        sf::Vector2f speed = {0, 0};
        sf::Vector2f pos = GetPoint();
    };
    bool isMouseIn();
    void Draw();
    void SetRoot(Node* vertex);
    void setZoom(float delta);
    void SetSize(sf::Vector2u size_);
    void SetFullSize(sf::Vector2u size_);
    void SetPos(sf::Vector2f pos_);
    void SetFullPos(sf::Vector2f pos_);
    void SetActive(bool flag, int f);
    bool getActive();
    int GetFull();
    void Scroll(std::pair<int, int> a);
private:

    void SetSize_(sf::Vector2u size_);
    void SetPos_(sf::Vector2f pos_);

    std::string title_;
    RoundedRectangle back;

    bool Active = false;
    int fullScreen = 0;
    int fullStep = 35;
    sf::Color ColActive = sf::Color::White;

    sf::Font font;
    Node* root = nullptr;
    static sf::Vector2f GetPoint();
    static int64_t GetSize(Node* root);
    void Phisic(std::vector<Node*>& points);
    std::vector<Node*> AllNodes(Node* v);
    std::chrono::steady_clock::time_point prev;

    sf::Vector2f pos, pos_rt, shift = { 0, 0 };
    sf::Vector2u size, size_rt;
    sf::RenderTexture texture;

    sf::Vector2f full_pos;
    sf::Vector2u full_size;

    Button *zoom_up, *zoom_down, *focus;

    float zoom = 1;
    float RADIUS = 40;
    float GRAVITY = 10;
    float Lateral = 2;
    float elasticity = 300;
    float K = 0.05;
};

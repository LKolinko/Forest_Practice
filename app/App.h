#include "../core/AVL.h"
#include "../core/RBTree.h"
#include "../core/Splay.h"
#include "../core/Treap.h"
#include "../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics.hpp"
#include "Button.h"
#include "Screen.h"
#include "Table.h"
#include "TextBox.h"

class App {
public:
    App();
    void Run();
private:
    void AddVertex(std::string value);
    void AddMTVertex();
    void RemoveVertex(int i, TreeDrawer::Node* q);
    std::chrono::steady_clock::time_point prev;
    void EventHandler(sf::Event& event);
    void ReWrite(sf::Event& event);
    AVLTree AVL;
    Treap treap;
    SplayTree splay;
    RBTree rb_tree_;
    Table* table_;
    int fullInd = -1;
    std::vector<TreeDrawer*> drawers_;
    std::vector<Button*> buttons;
    std::vector<std::pair<std::vector<float>, std::string>> buttons_settings = {
            { { 0.17, 0.05, 0.01, 0.1 }, "ADD" },
            { { 0.17, 0.05, 0.01, 0.25 }, "ADD" },
    };
    std::vector<TextBox*> textboxs;
    std::vector<std::pair<std::vector<float>, std::string>> textboxs_settings = {
            { { 0.17, 0.08, 0.01, 0.01 }, "Value: " },
            { { 0.17, 0.08, 0.01, 0.16 }, "mt19937: " },
    };
    int focus = -1;
    int cnt = 0;
};

#pragma once
#include "TreeDrawer.h"

class Treap {
public:
    Treap() = default;
    struct node : public TreeDrawer::Node {
        node(int64_t v);
        TreeDrawer::Node *GetLeft() const override {
            return l;
        }
        TreeDrawer::Node *GetRight() const override {
            return r;
        }
        std::string GetData() const override {
            std::string ans = "(" + std::to_string(val) + ";" + std::to_string(y) + ")";
            return std::to_string(val);
        }
        node *l = nullptr, *r = nullptr;
        int64_t y;
    };
    node* GetRoot();
    void Insert(int64_t val);
private:
    node* root = nullptr;
    std::pair<node*, node*> split(node* a, int64_t val);
    node* merge(node* a, node* b);
    node* find(node* a, int64_t val);
};


//
// Created by lkolinko on 5/12/24.
//

#ifndef RBTREE_H
#define RBTREE_H
#include "TreeDrawer.h"


class RBTree {
public:
    struct node : public TreeDrawer::Node {
        node(int64_t v);
        TreeDrawer::Node *GetLeft() const override {
            return l;
        }
        TreeDrawer::Node *GetRight() const override {
            return r;
        }
        std::string GetData() const override {
            return std::to_string(val);
        }
        node *l = nullptr, *r = nullptr, *prev = nullptr;
        bool is_empty = false;
    };
    node* GetRoot();
    void Insert(int64_t val);
    void Erase(int64_t val);
private:
    node* find(node* v, int64_t val);
    void LeftRotate(node* a);
    void RightRotate(node* a);
    void InsRebalance(node* a);
    void Delete(int64_t val);
    sf::Color GetColor(node* a);
    node* GetMin(node* a);
    node* root = nullptr;

    void Ins(node* v, int64_t val);
};

#endif //RBTREE_H

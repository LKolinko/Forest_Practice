//
// Created by lkolinko on 5/12/24.
//

#include "RBTree.h"

RBTree::node::node(int64_t v) : Node(v) {
    color = sf::Color::Red;
}

void RBTree::Ins(node* v, int64_t val) {
    if (v->val > val) {
        if (v->l == nullptr) {
            v->l = new node(val);
            v->l->prev = v;
            return;
        }
        Ins(v->l, val);
    } else {
        if (v->r == nullptr) {
            v->r = new node(val);
            v->r->prev = v;
            return;
        }
        Ins(v->r, val);
    }
}

void RBTree::Insert(int64_t val) {
    if (root == nullptr) {
        root = new node(val);
    }
    Ins(root, val);
    if (root->color == sf::Color::Red) {
        root->color = sf::Color::Black;
    }
}

void RBTree::InsRebalance(node *a) {
    if (a->color != sf::Color::Red || GetColor(a) != GetColor(a->prev)) {
        return;
    }

}

RBTree::node *RBTree::GetRoot() {
    return root;
}

int RBTree::GetColor(node *a) {
    if (a == nullptr) {
        return 0;
    }
    if (a->color == sf::Color::Magenta) {
        return 2;
    }
    return (a->color == sf::Color::Black ? 0 : 1);
}
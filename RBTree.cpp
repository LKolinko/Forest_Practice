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
            InsRebalance(v->l);
            return;
        }
        Ins(v->l, val);
    } else {
        if (v->r == nullptr) {
            v->r = new node(val);
            v->r->prev = v;
            InsRebalance(v->r);
            return;
        }
        Ins(v->r, val);
    }
    InsRebalance(v);
}

void RBTree::Insert(int64_t val) {
    if (find(root, val) != nullptr) {
        return;
    }
    if (root == nullptr) {
        root = new node(val);
    } else {
        Ins(root, val);
    }
    if (root->color == sf::Color::Red) {
        root->color = sf::Color::Black;
    }
}

RBTree::node *RBTree::find(node* v, int64_t val) {
    if (!v) {
        return nullptr;
    }
    if (v->val == val) {
        return v;
    }
    if (v->val > val) {
        return find(v->l, val);
    }
    return find(v->r, val);
}

void RBTree::LeftRotate(node *a) {
    node *p = a->prev;
    node *r = a->r;
    if (p) {
        if (p->l == a) {
            p->l = r;
        } else {
            p->r = r;
        }
    }

    a->color = sf::Color::Red;
    a->r->color = sf::Color::Black;

    node *tmp = r->l;
    r->l = a;
    a->r = tmp;
    a->prev = r;
    r->prev = p;

    if (a->r) {
        a->r->prev = a;
    }
}

void RBTree::RightRotate(node *a) {
    node* p = a->prev;
    node* l = a->l;
    if (p) {
        if (p->r == a) {
            p->r = l;
        } else {
            p->l = l;
        }
    }

    a->color = sf::Color::Red;
    a->l->color = sf::Color::Black;

    node* tmp = l->r;
    l->r = a;
    a->l = tmp;
    a->prev = l;
    l->prev = p;

    if (a->l) {
        a->l->prev = a;
    }
}

void RBTree::InsRebalance(node *a) {
    if (!a->prev) return;
    if (!a->prev->prev || a->color != sf::Color::Red || GetColor(a) != GetColor(a->prev)) {
        return;
    }
    if (a->prev->prev->l == a->prev) {
        if (GetColor(a->prev->prev->r) == sf::Color::Black) {
            if (a->prev->r == a) {
                LeftRotate(a->prev);
                RightRotate(a->prev);
            } else {
                RightRotate(a->prev->prev);
            }
        } else {
            a->prev->prev->r->color = sf::Color::Black;
            a->prev->prev->color = sf::Color::Red;
            a->prev->color = sf::Color::Black;
        }
    } else {
        if (GetColor(a->prev->prev->l) == sf::Color::Black) {
            if (a->prev->l == a) {
                RightRotate(a->prev);
                LeftRotate(a->prev);
            } else {
                LeftRotate(a->prev->prev);
            }
        } else {
            a->prev->prev->l->color = sf::Color::Black;
            a->prev->prev->color = sf::Color::Red;
            a->prev->color = sf::Color::Black;
        }
    }

    if (a->prev->prev == nullptr) {
        root = a->prev;
    }
}

RBTree::node *RBTree::GetRoot() {
    return root;
}

sf::Color RBTree::GetColor(node *a) {
    if (a == nullptr) {
        return sf::Color::Black;
    }
    return a->color;
}
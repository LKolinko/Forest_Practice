//
// Created by lkolinko on 4/30/24.
//

#include "Treap.h"

Treap::node::node(int64_t v) : Node(v) {
    std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    y = gen();
}

Treap::node *Treap::merge(Treap::node *a, Treap::node *b) {
    if (!a) {
        return b;
    }
    if (!b) {
        return a;
    }
    if (a->y > b->y) {
        a->r = merge(a->r, b);
        return a;
    }
    b->l = merge(a, b->l);
    return b;
}

std::pair<Treap::node*, Treap::node*> Treap::split(Treap::node *a, int64_t val) {
    if (a == nullptr) {
        return {nullptr, nullptr};
    }
    if (a->val <= val) {
        auto p = split(a->r, val);
        a->r = p.first;
        return {a, p.second};
    }
    auto p = split(a->l, val);
    a->l = p.second;
    return {p.first, a};
}

Treap::node *Treap::find(Treap::node *a, int64_t val) {
    if (!a) {
        return nullptr;
    }
    if (a->val == val) {
        return a;
    }
    if (a->val > val) {
        return find(a->l, val);
    }
    return find(a->r, val);
}

void Treap::Insert(int64_t val) {
    if (find(root, val)) {
        return;
    }
    auto new_node = new node(val);
    auto[low, up] = split(root, val);
    root = merge(low, merge(new_node, up));
}

Treap::node *Treap::GetRoot() {
    return root;
}

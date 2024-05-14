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
void RBTree::Erase(int64_t val) {
    Delete(val);
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

    auto color = a->r->color;
    a->r->color = a->color;
    a->color = color;

    node *tmp = r->l;
    r->l = a;
    a->r = tmp;
    a->prev = r;
    r->prev = p;

    if (a->r) {
        a->r->prev = a;
    }
    if (r->prev == nullptr) {
        root = r;
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

    auto color = a->l->color;
    a->l->color = a->color;
    a->color = color;

    node* tmp = l->r;
    l->r = a;
    a->l = tmp;
    a->prev = l;
    l->prev = p;

    if (a->l) {
        a->l->prev = a;
    }
    if (l->prev == nullptr) {
        root = l;
    }
}

void RBTree::InsRebalance(node *a) {
    if (!a->prev)
        return;
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

    if (a->prev == nullptr) {
        root = a;
    } else if (a->prev->prev == nullptr) {
        root = a->prev;
    }
}

void RBTree::Delete(int64_t val) {
    auto q = find(root, val);
    auto replase = GetMin(q->r);
    if (replase == nullptr && q == root) {
        root = (root->l ? root->l : nullptr);
        if (root != nullptr) {
            root->prev = nullptr;
            root->color = sf::Color::Black;
        }
        delete q;
        return;
    }
    if (replase == nullptr && q->l) {
        RightRotate(q);
        q->prev->r = nullptr;
        delete q;
        return;
    }
    if (replase == nullptr) {
        replase = q;
    }

    q->val = replase->val;

    if (replase->color == sf::Color::Red && !replase->l && !replase->r) {
        if (replase->prev->l == replase) {
            replase->prev->l = nullptr;
        } else {
            replase->prev->r = nullptr;
        }
        delete replase;
        return;
    }
    replase->is_empty = true;
    replase->color = sf::Color::Magenta;

    while (replase->color == sf::Color::Magenta) {
        if (replase->prev == nullptr) {
            replase->color = sf::Color::Black;
            root = replase;
            break;
        }
        // проверка положения
        if (replase->prev->l == replase) {
            // first
            if (GetColor(replase->prev->r) == sf::Color::Red &&
                GetColor(replase->prev->r->l) == sf::Color::Black &&
                GetColor(replase->prev->r->r) == sf::Color::Black) {
                LeftRotate(replase->prev);
            } else
            // second
            if (GetColor(replase->prev->r) == sf::Color::Black &&
                GetColor(replase->prev->r->l) == sf::Color::Black &&
                GetColor(replase->prev->r->r) == sf::Color::Black) {
                replase->prev->r->color = sf::Color::Red;
                if (replase->prev->color == sf::Color::Red) {
                    replase->prev->color = sf::Color::Black;
                } else {
                    replase->prev->color = sf::Color::Magenta;
                }
                auto e = replase->prev;
                if (replase->is_empty) {
                    replase->prev->l = nullptr;
                    delete replase;
                } else {
                    replase->color = sf::Color::Black;
                }
                replase = e;
            } else
            // third
            if (GetColor(replase->prev->r) == sf::Color::Black &&
                GetColor(replase->prev->r->l) == sf::Color::Red &&
                GetColor(replase->prev->r->r) == sf::Color::Black) {
                RightRotate(replase->prev->r);
            } else
            // fourth
            if (GetColor(replase->prev->r) == sf::Color::Black &&
                GetColor(replase->prev->r->r) == sf::Color::Red) {
                LeftRotate(replase->prev);
                replase->prev->prev->r->color = sf::Color::Black;
                replase->color = sf::Color::Black;
                auto e = replase;
                if (replase->is_empty) {
                    e->prev->l = nullptr;
                    delete replase;
                }
                break;
            }
        } else {
            // first
            if (GetColor(replase->prev->l) == sf::Color::Red &&
                GetColor(replase->prev->l->l) == sf::Color::Black &&
                GetColor(replase->prev->l->r) == sf::Color::Black) {
                RightRotate(replase->prev);
            } else
            // second
            if (GetColor(replase->prev->l) == sf::Color::Black &&
                GetColor(replase->prev->l->l) == sf::Color::Black &&
                GetColor(replase->prev->l->r) == sf::Color::Black) {
                replase->prev->l->color = sf::Color::Red;
                if (replase->prev->color == sf::Color::Red) {
                    replase->prev->color = sf::Color::Black;
                } else {
                    replase->prev->color = sf::Color::Magenta;
                }
                auto e = replase->prev;
                if (replase->is_empty) {
                    replase->prev->r = nullptr;
                    delete replase;
                } else {
                    replase->color = sf::Color::Black;
                }
                replase = e;
            } else
            // third
            if (GetColor(replase->prev->l) == sf::Color::Black &&
                GetColor(replase->prev->l->r) == sf::Color::Red &&
                GetColor(replase->prev->l->l) == sf::Color::Black) {
                LeftRotate(replase->prev->l);
            } else
            // fourth
            if (GetColor(replase->prev->l) == sf::Color::Black &&
                GetColor(replase->prev->l->l) == sf::Color::Red) {
                RightRotate(replase->prev);
                replase->prev->prev->l->color = sf::Color::Black;
                replase->color = sf::Color::Black;
                auto e = replase;
                if (replase->is_empty) {
                    e->prev->r = nullptr;
                    delete replase;
                }
                break;
            }
        }
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

RBTree::node *RBTree::GetMin(node *a) {
    if (!a) {
        return nullptr;
    }
    if (!a->l) {
        if (a->r) {
            LeftRotate(a);
        }
        return a;
    }
    return GetMin(a->l);
}

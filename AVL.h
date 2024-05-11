#pragma once
#include "TreeDrawer.h"
using namespace std;
using ll = long long;

class AVLTree {
public:
    struct node : public TreeDrawer::Node {
        node(int64_t v) : Node(v) {}
        TreeDrawer::Node *GetLeft() const override {
            return l;
        }
        TreeDrawer::Node *GetRight() const override {
            return r;
        }
        std::string GetData() const override {
            return std::to_string(val);
        }
        node *l = nullptr, *r = nullptr;
        ll hight = 1, balance = 0;
    };
    AVLTree(const AVLTree& other) {
        Clear(root);
        root = other.root;
    }
    AVLTree() = default;
    ~AVLTree() {
        Clear(root);
    }
    AVLTree &operator=(AVLTree& other) {
        Clear(root);
        root = other.root;
        return *this;
    }
    node* getRoot() {
        return root;
    }
    void Add(ll key) {
        if (!find(key)) {
            root = Insert(key, root);
        }
    }
    void PrintIn() {
        InOrder(root);
        cout << '\n';
    }
    void PrintPre() {
        PreOrder(root);
        cout << '\n';
    }
    void PrintPost() {
        PostOrder(root);
        cout << '\n';
    }
    bool find(ll val) {
        return findElem(val, root);
    }
    void Erase(ll v) {
        if (find(v)) {
            root = Delete(root, v);
        }
    }
private:

    node* root = nullptr;

    node* findElem(ll val, node* v) {
        if (v == nullptr) {
            return nullptr;
        }
        if (v->val == val) {
            return v;
        }
        if (v->val > val) {
            return findElem(val, v->l);
        }
        return findElem(val, v->r);
    }

    node* getMin(node* v) {
        if (v == nullptr) {
            return nullptr;
        }
        if (v->l == nullptr) {
            return v;
        }
        return getMin(v->l);
    }

    node* EraseMin(node* v) {
        if (v == nullptr) {
            return nullptr;
        }
        if (v->l == nullptr) {
            return v->r;
        }
        v->l = EraseMin(v->l);
        return balance(v);
    }

    node* Delete(node* v, ll key) {
        if (v == nullptr) {
            return nullptr;
        }
        if (v->val > key) {
            v->l = Delete(v->l, key);
        } else if (v->val < key) {
            v->r = Delete(v->r, key);
        } else if (v->val == key) {
            auto u = getMin(v->r);
            if (!u) {
                auto e = v->l;
                delete v;
                return balance(e);
            }
            v->r = EraseMin(v->r);
            u->r = v->r;
            u->l = v->l;
            delete v;
            return balance(u);
        }
        return balance(v);
    }

    void Clear(node* v) {
        if (v == nullptr) {
            return;
        }
        Clear(v->l);
        Clear(v->r);
        delete v;
    }

    ll getHight(node* a) {
        return a ? a->hight : 0;
    }
    ll getBalance(node* a) {
        return a ? a->balance : 0;
    }
    void upd(node* a) {
        if (a == nullptr) {
            return;
        }
        a->hight = max(getHight(a->l), getHight(a->r)) + 1;
        a->balance = getHight(a->l) - getHight(a->r);
    }

    node* LeftRotate(node* a) {
        if (a == nullptr) {
            return a;
        }
        auto p = a->r;
        a->r = p->l;
        p->l = a;
        upd(a);
        upd(p);
        return p;
    }

    node* RightRotate(node* a) {
        if (a == nullptr) {
            return a;
        }
        auto p = a->l;
        a->l = p->r;
        p->r = a;
        upd(a);
        upd(p);
        return p;
    }

    node* LeftRightRotate(node* a) {
        a->r = RightRotate(a->r);
        a = LeftRotate(a);
        return a;
    }

    node* RightLeftRotate(node* a) {
        a->l = LeftRotate(a->l);
        a = RightRotate(a);
        return a;
    }

    node* balance(node* a) {
        upd(a);
        if (getBalance(a) == -2) {
            if (getBalance(a->r) == 1) {
                a = LeftRightRotate(a);
            } else {
                a = LeftRotate(a);
            }
        } else if (getBalance(a) == 2) {
            if (getBalance(a->l) == -1) {
                a = RightLeftRotate(a);
            } else {
                a = RightRotate(a);
            }
        }
        return a;
    }

    node* Insert(ll val, node* v) {
        if (v == nullptr) {
            node* q = new node(val);
            return q;
        }
        if (v->val > val) {
            v->l = Insert(val, v->l);
            return balance(v);
        }
        v->r = Insert(val, v->r);
        return balance(v);
    }

    void InOrder(node* v) {
        if (v == nullptr) {
            return;
        }
        InOrder(v->l);
        cout << v->val << ' ';
        InOrder(v->r);
    }

    void PreOrder(node* v) {
        if (v == nullptr) {
            return;
        }
        cout << v->val << ' ';
        PreOrder(v->l);
        PreOrder(v->r);
    }

    void PostOrder(node* v) {
        if (v == nullptr) {
            return;
        }
        PostOrder(v->l);
        PostOrder(v->r);
        cout << v->val << ' ';
    }
};
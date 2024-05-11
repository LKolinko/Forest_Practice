#include "TreeDrawer.h"

class SplayTree {
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
        node *l = nullptr, *r = nullptr, *prev = nullptr;
    };

    void Insert(int64_t value) {
        node* q = new node(value);
        if (!root) {
            root = q;
            return;
        }
        Ins(root, q);
    }

    node* GetRoot() {
        return root;
    }
private:
    node* root = nullptr;

    void LeftRotate(node* a) {
        node* p = a->prev;
        node* r = a->r;
        if (p) {
            if (p->l == a) {
                p->l = r;
            } else {
                p->r = r;
            }
        }
        node* tmp = r->l;
        r->l = a;
        a->r = tmp;
        a->prev = r;
        r->prev = p;
        if (a->r) {
            a->r->prev = a;
        }
    }
    void RightRotate(node* a) {
        node* p = a->prev;
        node* l = a->l;
        if (p) {
            if (p->r == a) {
                p->r = l;
            } else {
                p->l = l;
            }
        }
        node* tmp = l->r;
        l->r = a;
        a->l = tmp;
        a->prev = l;
        l->prev = p;
        if (a->l) {
            a->l->prev = a;
        }
    }
    void splay(node* v) {
        while (true) {
            if (v->prev == nullptr) {
                root = v;
                break;
            }
            if (v->prev->prev == nullptr) {
                if (root->l == v) {
                    RightRotate(root);
                } else {
                    LeftRotate(root);
                }
                root = v;
                break;
            }
            if (v->prev->l == v && v->prev->prev->l == v->prev) {
                // zig-zig
                RightRotate(v->prev->prev);
                RightRotate(v->prev);
            } else if (v->prev->r == v && v->prev->prev->r == v->prev) {
                // zag-zag
                LeftRotate(v->prev->prev);
                LeftRotate(v->prev);
            } else if (v->prev->r == v && v->prev->prev->l == v->prev) {
                // zig-zag
                LeftRotate(v->prev);
                RightRotate(v->prev);
            } else if (v->prev->l == v && v->prev->prev->r == v->prev) {
                // zag-zig
                RightRotate(v->prev);
                LeftRotate(v->prev);
            }
        }
    }

    void Ins(node* v, node* val) {
        if (v->val > val->val) {
            if (v->l == nullptr) {
                v->l = val;
                val->prev = v;

                splay(val);
                return;
            }
            Ins(v->l, val);
        } else {
            if (v->r == nullptr) {
                v->r = val;
                val->prev = v;
                splay(val);
                return;
            }
            Ins(v->r, val);
        }
    }
};
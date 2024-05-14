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
        if (!find(root, value)) {
            node* q = new node(value);
            if (!root) {
                root = q;
                return;
            }
            Ins(root, q);
        }
    }

    void Erase(int64_t val) {
        auto q = find(root, val);
        if (!q) {
            return;
        }
        root = splay(q, root);
        auto a = root->l, b = root->r;
        if (a) {
            a->prev = nullptr;
        }
        if (b) {
            b->prev = nullptr;
        }
        root = merge(a, b);
        delete q;
    }

    node* GetRoot() {
        return root;
    }
private:
    node* root = nullptr;

    node* merge(node* a, node* b) {
        a = splay(findMax(a), a);
        if (a) {
            a->r = b;
            if (b) {
                b->prev = a;
            }
            return a;
        }
        return b;
    }

    node* findMax(node* v) {
        if (v == nullptr) {
            return nullptr;
        }
        if (v->r == nullptr) {
            return v;
        }
        return findMax(v->r);
    }

    node* find(node* v, int64_t val) {
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
    node* splay(node* v, node* rt) {
        if (v == nullptr) {
            return nullptr;
        }
        while (true) {
            if (v->prev == nullptr) {
                break;
            }
            if (v->prev->prev == nullptr) {
                if (rt->l == v) {
                    RightRotate(rt);
                } else {
                    LeftRotate(rt);
                }
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
        return v;
    }

    void Ins(node* v, node* val) {
        if (v->val > val->val) {
            if (v->l == nullptr) {
                v->l = val;
                val->prev = v;

                root = splay(val, root);
                return;
            }
            Ins(v->l, val);
        } else {
            if (v->r == nullptr) {
                v->r = val;
                val->prev = v;
                root = splay(val, root);
                return;
            }
            Ins(v->r, val);
        }
    }
};
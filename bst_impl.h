//
// Created by Olivier Cuisenaire on 23.05.20.
//

#ifndef ASD1_LABS_2020_BST_IMPL_H
#define ASD1_LABS_2020_BST_IMPL_H

// fonctions récursives n'ayant pas à connaitre root

#include "bst.h"

template<typename Key>
void bst<Key>::copyPreOrderFromSource(Node<Key> *&dest, Node<Key> *source) {
    if (source) {
        dest = new Node<Key>{source->key, nullptr, nullptr};
        copyPreOrderFromSource(dest->left, source->left);
        copyPreOrderFromSource(dest->right, source->right);
    }
}

template<typename Key>
void bst<Key>::destroyPostOrder(Node<Key> *dest) {
    if (dest) {
        destroyPostOrder(dest->left);
        destroyPostOrder(dest->right);
        delete dest;
    }
}

template<typename Key>
Node<Key> *bst<Key>::search(Node<Key> *p, const Key &k) noexcept {
    if (p == nullptr) {
        return nullptr;
    } else if (p->key == k) {
        return p;
    } else if (k < p->key) {
        return search(p->left, k);
    } else {
        return search(p->right, k);
    }
}

template<typename Key>
Node<Key> *bst<Key>::min(Node<Key> *p) noexcept {
    Node<Key> *m = p;
    while (m->left) {
        m = m->left;
    }
    return m;
}

template<typename Key>
Node<Key> *bst<Key>::max(Node<Key> *p) noexcept {
    Node<Key> *m = p;
    while (m->right) {
        m = m->right;
    }
    return m;
}

template<typename Key>
void bst<Key>::eraseMin(Node<Key> *&p) {
    if (p->left) {
        eraseMin(p->left);
    } else {
        Node<Key> *d = p->right;
        delete p;
        p = d;
    }
}


template<typename Key>
void bst<Key>::eraseMax(Node<Key> *&p) {
    if (p->right) {
        eraseMax(p->right);
    } else {
        Node<Key> *d = p->left;
        delete p;
        p = d;
    }
}

template<typename Key>
void bst<Key>::erase(Node<Key> *&p, const Key &k) noexcept {
    if (p == nullptr) {
        return;
    } else if (k < p->key) {
        erase(p->left, k);
    } else if (k > p->key) {
        erase(p->right, k);
    } else {
        Node<Key> *tmp = p;
        if (p->left == nullptr) {
            p = p->right;
        } else if (p->right == nullptr) {
            p = p->left;
        } else {
            Node<Key> *m = splice_min(p->right);
            m->right = p->right;
            m->left = p->left;
            p = m;
            delete tmp;
        }
    }
}

template<typename Key>
Node<Key> *bst<Key>::splice_min(Node<Key> *&p) noexcept {
    if (p->left) {
        splice_min(p->left);
    } else {
        Node<Key> *d = p;
        p = p->right;
        return d;
    }
}


template<typename Key>
template<typename Fn>
void bst<Key>::visitSymetric(Node<Key> *dest, Fn f) {
    if (dest) {
        visitSymetric(dest->left, f);
        f(dest->key);
        visitSymetric(dest->right, f);
    }
}

template<typename Key>
void bst<Key>::linearize(Node<Key> *r, Node<Key> *&L, size_t &n) noexcept{
    if (r) {
        linearize(r->right, L, n);
        Node<Key> *temp = r;
        r->right = L;
        L = temp;
        ++n;
        linearize(r->left, L, n);
        r->left = nullptr;
    }
}

template<typename Key>
Node<Key> * bst<Key>::arborize(Node<Key> *&L, size_t n) noexcept{
    if (n != 0){
        Node<Key> * rg = arborize(L, (n-1)/2);
        Node<Key> *r = L;
        r->left = rg;
        L = L->right;
        r->right = arborize(L, n/2);
        return r;
    }
    return nullptr;
}

template<typename Key>
void bst<Key>::insert(Node<Key> *&r, Key const &k) {
    if (r == nullptr) {
        r = new Node<Key>{k, nullptr, nullptr};
    } else if (k == r->key) {
        // k already there : do nothing.
    } else if (k < r->key) {
        insert(r->left, k);
    } else { // k > r->key
        insert(r->right, k);
    }
}

template<typename Key>
void bst<Key>::to_stream(Node<Key> *r, std::ostream &s) noexcept {
    if (r) {
        s << r->key;
        if (r->right or r->left) { // r has children
            s << "(";
            if (r->left) to_stream(r->left, s);
            else s << ".";

            s << ",";

            if (r->right) to_stream(r->right, s);
            else s << ".";

            s << ")";
        }
    }
}

// méthodes de la classe bst

template<typename Key>
bst<Key>::bst() : root(nullptr) {
}

template<typename Key>
bst<Key>::~bst() {
    destroyPostOrder(root);
}

template<typename Key>
void bst<Key>::insert(Key const &k) {
    insert(root, k);
}

template<typename Key>
void bst<Key>::display_indented(std::ostream &s) const noexcept {
    displayIdent(s, root);
}

template<typename Key>
bst<Key>::bst(const bst &other) {
    copyPreOrderFromSource(root, other.root);
}

template<typename Key>
bst<Key> &bst<Key>::operator=(const bst &other) {
    if (this == &other) {
        return *this;
    }
    bst<Key> tmp{other};
    using std::swap;
    swap(root, tmp.root);
    return *this;
}

template<typename Key>
Key const &bst<Key>::min() const {
    if (root == nullptr) {
        throw std::exception();
    }

    return min(root)->key;

}

template<typename Key>
Key const &bst<Key>::max() const {
    if (root == nullptr) {
        throw std::exception();
    }
    return max(root)->key;
}

template<typename Key>
bool bst<Key>::contains(const Key &k) const noexcept {
    return search(root, k) != nullptr;
}

template<typename Key>
void bst<Key>::erase_min() {
    if (root == nullptr) {
        throw std::exception();
    }
    eraseMin(root);
}

template<typename Key>
void bst<Key>::erase_max() {
    if (root == nullptr) {
        throw std::exception();
    }
    eraseMax(root);
}

template<typename Key>
void bst<Key>::erase(const Key &k) noexcept {
    erase(root, k);
}

template<typename Key>
template<typename Fn>
void bst<Key>::visit_in_order(Fn f) const {
    visitSymetric(root, f);
}

template<typename Key>
std::ostream &bst<Key>::displayIdent(std::ostream &lhs, Node<Key> *r, const std::string &ident) {
    if (r != nullptr) {
        lhs << (r->key) << std::endl;
        std::string newIdent = ident + "|_ ";
        if (r->left || r->right) {
            if (r->left) {
                lhs << newIdent;
                newIdent.replace(newIdent.size() - 2, 1, " ");
                displayIdent(lhs, r->left, newIdent);
                newIdent = ident + "|_ ";
            } else {
                lhs << newIdent << "." << std::endl;
            }

            if (r->right) {
                lhs << newIdent;
                newIdent.replace(newIdent.size() - 3, 2, "  ");
                displayIdent(lhs, r->right, newIdent);
            } else {
                lhs << newIdent << "." << std::endl;
            }
        }

    }
    return lhs;
}

template<typename Key>
void bst<Key>::balance() noexcept {
    Node<Key> *l = nullptr;
    size_t n = 0;
    linearize(root, l, n);
    root = arborize(l,n);
}

template<typename Key>
void bst<Key>::linearize() noexcept {
    size_t n = 0;
    Node<Key> *l = nullptr;
    linearize(root, l, n);
    root = l;
}

template<typename Key>
std::ostream &operator<<(std::ostream &s, bst<Key> const &t) {
    bst<Key>::to_stream(t.root, s);
    return s;
}


#endif //ASD1_LABS_2020_BST_IMPL_H

//
// Created by Olivier Cuisenaire on 23.05.20.
//

#include <iostream>
#include "bst.h"

using namespace std;

template<typename T>
void afficher(T t) {
    cout << t << " ";
}

#include "util.h"

int main() {

    bst<C> t{};
/*
    for(int i : { 8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12 })
        t.insert(i);
        */

    cout <<endl;
    for(int i : { 7,8,5,6,2,1,3,4 })
        t.insert(i);
    cout << endl;
    bst<C> tree;
    cout << endl;
    t.display_indented(cout);
    cout <<  endl;
    t.linearize();
    cout << t << endl;
    t.balance();
    cout << t << endl;

  /*  bst<int> b{t};
    t.erase_min();
    t.erase_max();
    t.erase(6);
    t.erase(4);
    b.insert(300);
    t = b;
    t.visit_in_order(afficher<int>);
    cout << endl;
    cout << t << endl;
    cout << b << endl;
    cout << t.min()<<endl;
    cout << t.max()<<endl;
    */
}
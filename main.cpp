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

    bst<int> tree{};


    for (int i : {7, 8, 5, 6, 2, 1, 3, 4})
        tree.insert(i);
    tree.display_indented(cout);

    tree.balance();
    cout << endl;
    tree.display_indented(cout);
    cout << endl << tree;


}
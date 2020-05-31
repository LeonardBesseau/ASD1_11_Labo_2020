#include "catch.hpp"
#include "../bst.h"
#include "../util.h"

#include <sstream>
#include <string>


using namespace std;

template<typename T>
string to_string(T const &t) {
    ostringstream oss;
    oss << t;
    return oss.str();
}


template<typename T>
void afficher(T t) {
    cout << t << " ";
}

TEST_CASE("minimum", "[bst]") {
    GIVEN("A tree") {
        bst<int> tree;
        WHEN("the tree is empty") {
            THEN("An exception is raised") {
                REQUIRE_THROWS_AS(tree.min(), std::exception);
            }
        }WHEN("the tree has elements") {
            for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12}) {
                tree.insert(i);
            }
            THEN("the minimum element is returned") {
                REQUIRE(tree.min() == 1);
            }
        }WHEN("the tree has only one element") {
            tree.insert(42);
            THEN("the minimum element is returned") {
                REQUIRE(tree.min() == 42);
            }
        }
    }
}

TEST_CASE("max", "[bst]") {
    GIVEN("A tree") {
        bst<int> tree;
        WHEN("the tree is empty") {
            THEN("An exception is raised") {
                REQUIRE_THROWS_AS(tree.max(), std::exception);
            }
        }WHEN("the tree has elements") {
            for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12}) {
                tree.insert(i);
            }
            THEN("the maximum element is returned") {
                REQUIRE(tree.max() == 12);
            }
        }WHEN("the tree has only one element") {
            tree.insert(42);
            THEN("the maximum element is returned") {
                REQUIRE(tree.max() == 42);
            }
        }
    }
}

TEST_CASE("contains", "[bst]") {
    GIVEN("A tree") {
        bst<int> tree;
        WHEN("the tree is empty") {
            THEN("No value is contained in the tree") {
                REQUIRE(!tree.contains(1));
            }
        }WHEN("the tree has elements") {
            for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12}) {
                tree.insert(i);
            }
            THEN("the elements are contained in the tree") {
                REQUIRE(tree.contains(1));
                REQUIRE(tree.contains(2));
                REQUIRE(tree.contains(3));
                REQUIRE(tree.contains(4));
                REQUIRE(tree.contains(5));
                REQUIRE(tree.contains(6));
                REQUIRE(tree.contains(7));
                REQUIRE(tree.contains(8));
                REQUIRE(tree.contains(10));
                REQUIRE(tree.contains(11));
                REQUIRE(tree.contains(12));
            }THEN("missing elements are not contained in the tree") {
                REQUIRE(!tree.contains(0));
                REQUIRE(!tree.contains(9));
                REQUIRE(!tree.contains(13));
            }
        }
    }
}

TEST_CASE("erase_min", "[bst]") {
    GIVEN("A tree") {
        bst<int> tree;
        WHEN("the tree is empty") {
            THEN("An exception is raised") {
                REQUIRE_THROWS(tree.erase_min());
            }
        }WHEN("the tree has elements") {
            for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12}) {
                tree.insert(i);
            }
            tree.erase_min();
            THEN("the minimum element is erased") {
                REQUIRE(to_string(tree) == "8(4(2(.,3),6(5,7)),11(10,12))");
            }
        }WHEN("the tree has only one element") {
            tree.insert(42);
            tree.erase_min();
            THEN("the tree is empty") {
                REQUIRE(to_string(tree).empty());
            }
        }
    }
}

TEST_CASE("erase_max", "[bst]") {
    GIVEN("A tree") {
        bst<int> tree;
        WHEN("the tree is empty") {
            THEN("An exception is raised") {
                REQUIRE_THROWS(tree.erase_max());
            }
        }WHEN("the tree has elements") {
            for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12}) {
                tree.insert(i);
            }
            tree.erase_max();
            THEN("the maximum element is erased") {
                REQUIRE(to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,.))");
            }
        }WHEN("the tree has only one element") {
            tree.insert(42);
            tree.erase_max();
            THEN("the tree is empty") {
                REQUIRE(to_string(tree).empty());
            }
        }
    }
}

TEST_CASE("erase", "[bst]") {
    GIVEN("A tree") {
        bst<int> tree;
        WHEN("the tree is empty") {
            THEN("No exception is raised") {
                REQUIRE_NOTHROW(tree.erase(1));
            }
        }WHEN("the tree has elements") {
            for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12}) {
                tree.insert(i);
            }
            THEN("if the deleted element has two children, the minimum of its right children replace it") {
                tree.erase(4);
                REQUIRE(to_string(tree) == "8(5(1(.,2(.,3)),6(.,7)),11(10,12))");
            }THEN("if the deleted element has only one child, the child replace him") {
                // check right side
                tree.erase(2);
                REQUIRE(to_string(tree) == "8(4(1(.,3),6(5,7)),11(10,12))");
                //add element to check left side
                tree.insert(2);
                REQUIRE(to_string(tree) == "8(4(1(.,3(2,.)),6(5,7)),11(10,12))");
                //check left side
                tree.erase(3);
                REQUIRE(to_string(tree) == "8(4(1(.,2),6(5,7)),11(10,12))");
            }THEN("if the deleted element has no children, no further change to the tree") {
                tree.erase(10);
                REQUIRE(to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(.,12))");
                tree.erase(12);
                REQUIRE(to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11)");
            }THEN("if the root is deleted the tree is still valid") {
                tree.erase(8);
                REQUIRE(to_string(tree) == "10(4(1(.,2(.,3)),6(5,7)),11(.,12))");
            }THEN("if the element is not in the tree, the tree is not modified") {
                tree.erase(9);
                REQUIRE(to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))");
            }
        }WHEN("the tree has only one element") {
            tree.insert(42);

            THEN("if the element is erase, the tree is empty") {
                tree.erase(42);
                REQUIRE(to_string(tree).empty());
            }THEN("if the element is not in the tree, the tree is not modified") {
                tree.erase(9);
                REQUIRE(to_string(tree) == "42");
            }
        }
    }
}

TEST_CASE("visit_in_order", "[bst]") {
    GIVEN("A tree") {
        bst<int> tree;
        WHEN("the tree is empty") {
            THEN("No exception is raised") {
                std::ostringstream oss;
                std::streambuf *pCout = cout.rdbuf(); // pointer to restore cout later
                cout.rdbuf(oss.rdbuf()); // redirect output
                tree.visit_in_order(afficher<int>);
                cout.rdbuf(pCout); // restore cout
                REQUIRE(oss.str().empty());
            }
        }WHEN("the tree has elements") {
            for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12}) {
                tree.insert(i);
            }
            THEN("The tree is display in order") {
                std::ostringstream oss;
                std::streambuf *pCout = cout.rdbuf(); // pointer to restore cout later
                cout.rdbuf(oss.rdbuf()); // redirect output
                tree.visit_in_order(afficher<int>);
                cout.rdbuf(pCout); // restore cout
                REQUIRE(oss.str() == "1 2 3 4 5 6 7 8 10 11 12 ");
            }
        }
    }
}

TEST_CASE("linearize", "[bst]") {
    GIVEN("A tree") {
        bst<int> tree;
        WHEN("the tree is empty") {
            THEN("Nothing happens") {
                REQUIRE_NOTHROW(tree.linearize());
                REQUIRE(to_string(tree).empty());
            }
        }WHEN("the tree has elements") {
            for (int i : {7, 8, 5, 6, 2, 1, 3, 4})
                tree.insert(i);
            THEN("the tree is linearized") {
                tree.linearize();
                REQUIRE(to_string(tree) == "1(.,2(.,3(.,4(.,5(.,6(.,7(.,8)))))))");
            }
        }WHEN("the tree has only one element") {
            tree.insert(42);
            THEN("Nothing happens") {
                tree.linearize();
                REQUIRE(to_string(tree) == "42");
            }
        }WHEN("the tree is already linearized") {
            for (int i : {1, 2, 3, 4, 5, 6, 7, 8})
                tree.insert(i);
            THEN("Nothing happens") {
                tree.linearize();
                REQUIRE(to_string(tree) == "1(.,2(.,3(.,4(.,5(.,6(.,7(.,8)))))))");
            }
        }
    }
}


TEST_CASE("destructor", "[bst]") {

    GIVEN("An empty tree") {
        WHEN("the destructor is called") {
            THEN("The object is detroyed with no other call") {
                std::ostringstream oss;
                std::streambuf *pCout = cout.rdbuf(); // pointer to restore cout later
                cout.rdbuf(oss.rdbuf()); // redirect output

                {

                    bst<C> tree;
                }
                REQUIRE(oss.str().empty());
                cout.rdbuf(pCout); // restore cout

            }
        }
    }

    GIVEN("A tree with some element") {
        WHEN("the destructor is called") {
            THEN("The object and each element in it too") {
                std::ostringstream oss;
                std::streambuf *pCout = cout.rdbuf(); // pointer to restore cout later
                cout.rdbuf(oss.rdbuf()); // redirect output

                {
                    bst<C> tree;
                    for (int i : {7, 8, 5, 6, 2, 1, 3, 4})
                        tree.insert(i);
                }
                REQUIRE(oss.str() ==
                        " C(7)  CP(7)  D(7)  C(8)  CP(8)  D(8)  C(5)  CP(5)  D(5)  C(6)  CP(6)  D(6)  C(2) "
                        " CP(2)  D(2)  C(1)  CP(1)  D(1)  C(3)  CP(3)  D(3)  C(4)  CP(4)  D(4) "
                        " D(1)  D(4)  D(3)  D(2)  D(6)  D(5)  D(8)  D(7) "
                );
                cout.rdbuf(pCout); // restore cout
            }
        }
    }
}

TEST_CASE("copy constructor", "[bst]") {
    GIVEN("An empty tree") {
        bst<int> tree;
        WHEN("a copy is created") {
            THEN("The copy is empty") {
                bst<int> newTree{tree};
                REQUIRE(to_string(newTree).empty());
            }
        }
    }GIVEN("A tree with some element") {
        bst<C> tree;
        for (int i : {7, 8, 5, 6, 2, 1, 3, 4})
            tree.insert(i);
        WHEN("a copy is created") {
            bst<C> newTree{tree};
            THEN("The new tree has the same value as the original") {
                REQUIRE(to_string(newTree) == to_string(tree));
            }AND_THEN("A modification on one of the tree does not modify the other") {
                tree.erase_min();
                REQUIRE(to_string(newTree) != to_string(tree));
                newTree.insert(300);
                REQUIRE(!tree.contains(300));
            }
        }
    }

    GIVEN("A tree with some element that might throw") {
        std::ostringstream oss;
        std::streambuf *pCout = cout.rdbuf(); // pointer to restore cout later
        cout.rdbuf(oss.rdbuf()); // redirect output
        bst<C> tree;
        for (int i : {7, 8, 5, 6})
            tree.insert(i);
        tree.insert({2, 1});
        for (int i : {1, 3, 4})
            tree.insert(i);
        oss.str("");
        WHEN("a copy is created and an exception occur") {
            try {
                bst<C> newTree{tree};
                REQUIRE(false);
            } catch (const std::exception &) {
                THEN("The copy is destroyed properly") {
                    REQUIRE(oss.str() == " CP(7)  CP(5)  D(5)  D(7) ");
                }AND_THEN("The source tree is still valid"){
                    REQUIRE(to_string(tree) == "7(5(2(1,3(.,4)),6),8)");
                }
            }
        }
        cout.rdbuf(pCout); // restore cout
    }

}

TEST_CASE("copy assignement operator", "[bst]") {
    GIVEN("Two empty trees") {
        bst<int> tree;
        bst<int> newTree;
        WHEN("The assignation is done") {
            THEN("The copy is also empty") {

                newTree = tree;
                REQUIRE(to_string(newTree).empty());
            }
        }
    }GIVEN("One tree with element and one empty tree") {
        bst<int> tree;
        for (int i : {7, 8, 5, 6, 2, 1, 3, 4})
            tree.insert(i);
        bst<int> newTree;
        WHEN("the full tree is assigned the empty tree") {
            THEN("The full tree is now empty") {
                tree = newTree;
                REQUIRE(to_string(newTree).empty());
            }
        }WHEN("the empty tree is assigned the full tree") {
            THEN("The empty tree has copied element from the full tree") {
                newTree = tree;
                REQUIRE(to_string(newTree) == to_string(tree));
            }AND_THEN("A modification on one of the tree does not modify the other") {
                tree.erase_min();
                REQUIRE(to_string(newTree) != to_string(tree));
                newTree.insert(300);
                REQUIRE(!tree.contains(300));
            }
        }
    }
    GIVEN("Two trees with some element") {
        bst<C> tree;
        for (int i : {7, 8, 5, 6, 2, 1, 3, 4})
            tree.insert(i);
        bst<C> newTree;
        for (int i : {13, 14, 11, 12, 8, 7})
            newTree.insert(i);
        WHEN("the assigned tree has the element of the other tree") {
            tree = newTree;
            THEN("The new tree has the same value as the original") {
                REQUIRE(to_string(newTree) == to_string(tree));
            }AND_THEN("A modification on one of the tree does not modify the other") {
                tree.erase_min();
                REQUIRE(to_string(newTree) != to_string(tree));
                newTree.insert(300);
                REQUIRE(!tree.contains(300));
            }
        }
        GIVEN("Two trees and some element that might throw") {
            std::ostringstream oss;
            std::streambuf *pCout = cout.rdbuf(); // pointer to restore cout later
            cout.rdbuf(oss.rdbuf()); // redirect output
            bst<C> tree;
            for (int i : {7, 8, 5, 6})
                tree.insert(i);
            tree.insert({2, 1});
            for (int i : {1, 3, 4})
                tree.insert(i);
            bst<C> newTree;
            for (int i : {13, 14, 11, 12, 8, 7})
                newTree.insert(i);
            oss.str(""); // reset output to only get the assignment output
            WHEN("a copy is created and an exception occur") {
                try {
                    newTree = tree;
                    REQUIRE(false);
                } catch (const std::exception &) {
                    THEN("The copy is destroyed properly") {
                        REQUIRE(oss.str() == " CP(7)  CP(5)  D(5)  D(7) ");
                    }AND_THEN("The source tree is still valid"){
                        REQUIRE(to_string(tree) == "7(5(2(1,3(.,4)),6),8)");
                    }AND_THEN("The destination tree is still valid and has it's old element"){
                        REQUIRE(to_string(newTree) == "13(11(8(7,.),12),14)");
                    }
                }
            }
            cout.rdbuf(pCout); // restore cout
        }
    }
}

TEST_CASE("operator<<", "[bst]") {

    bst<int> tree;

    SECTION("Tree from ASD1 slides") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);
        REQUIRE(to_string(tree) == "8(4(1(.,2(.,3)),6(5,7)),11(10,12))");
    }

    SECTION("Empty tree") {
        REQUIRE(to_string(tree).empty());
    }
}

TEST_CASE("insert", "[bst]") {

    bst<int> tree;

    SECTION("Insert 42") {
        tree.insert(42);
        REQUIRE(to_string(tree) == "42");
    }

    SECTION("Insert smaller to the left") {
        tree.insert(3);
        tree.insert(2);
        REQUIRE(to_string(tree) == "3(2,.)");
    }

    SECTION("Insert larger to the right") {
        tree.insert(3);
        tree.insert(4);
        REQUIRE(to_string(tree) == "3(.,4)");
    }

    SECTION("Insert twice has no effect") {
        tree.insert(3);
        tree.insert(4);
        tree.insert(4);
        REQUIRE(to_string(tree) == "3(.,4)");
    }
}

TEST_CASE("display_indented", "[bst]") {
    bst<int> tree;

    SECTION("Tree from ASD1 slides") {
        for (int i : {8, 4, 1, 2, 3, 6, 5, 7, 11, 10, 12})
            tree.insert(i);

        ostringstream oss;
        tree.display_indented(oss);
        REQUIRE(oss.str() == "8\n"
                             "|_ 4\n"
                             "|  |_ 1\n"
                             "|  |  |_ .\n"
                             "|  |  |_ 2\n"
                             "|  |     |_ .\n"
                             "|  |     |_ 3\n"
                             "|  |_ 6\n"
                             "|     |_ 5\n"
                             "|     |_ 7\n"
                             "|_ 11\n"
                             "   |_ 10\n"
                             "   |_ 12\n");
    }
}
#include "HeightOf.h"
using namespace std;

int heightOf(Node* root) {
    (void) root;
    return -1;
}

/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"

PROVIDED_TEST("Works on an empty tree.") {
    EXPECT_EQUAL(heightOf(nullptr), -1);
}

PROVIDED_TEST("Works on single-node trees.") {
    Node* root = toTree("137");
    EXPECT_EQUAL(heightOf(root), 0);
    freeTree(root);
}

PROVIDED_TEST("Works on two-node trees.") {
    Node* root = toTree(R"(   137   )",
                        R"(     \   )",
                        R"(      42 )");
    EXPECT_EQUAL(heightOf(root), 1);
    freeTree(root);

    root = toTree(R"(   137   )",
                  R"(   /   )",
                  R"(  42 )");
    EXPECT_EQUAL(heightOf(root), 1);
    freeTree(root);
}

PROVIDED_TEST("Works on three-node trees.") {
    Node* root;
    root = toTree(R"(   137   )",
                  R"(   / \   )",
                  R"(  5   42 )");
    EXPECT_EQUAL(heightOf(root), 1);
    freeTree(root);

    root = toTree(R"(   137   )",
                  R"(   /     )",
                  R"(  42     )",
                  R"(  /      )",
                  R"( 9       )");
    EXPECT_EQUAL(heightOf(root), 2);
    freeTree(root);

    root = toTree(R"(   137   )",
                  R"(   /     )",
                  R"(  42     )",
                  R"(   \     )",
                  R"(    9    )");
    EXPECT_EQUAL(heightOf(root), 2);
    freeTree(root);

    root = toTree(R"(   137   )",
                  R"(    \    )",
                  R"(    42   )",
                  R"(     /   )",
                  R"(    9    )");
    EXPECT_EQUAL(heightOf(root), 2);
    freeTree(root);

    root = toTree(R"(   137   )",
                  R"(    \    )",
                  R"(    42   )",
                  R"(     \   )",
                  R"(      9  )");
    EXPECT_EQUAL(heightOf(root), 2);
    freeTree(root);
}

PROVIDED_TEST("Works on a more complex tree.") {
    Node* root;
    root = toTree(R"(      1       )",
                  R"(     / \      )",
                  R"(    /   2     )",
                  R"(   /   / \    )",
                  R"(  3   4   5   )",
                  R"( / \   \   \  )",
                  R"(6   7   8   9 )");
    EXPECT_EQUAL(heightOf(root), 3);
    freeTree(root);
}

#pragma once

#include "GUI/MemoryDiagnostics.h"

struct Node {
    int   value;
    Node* left;
    Node* right;

    TRACK_ALLOCATIONS_OF(Node);
};

/* Deletes all nodes in the given tree. */
inline void freeTree(Node* root) {
    if (root != nullptr) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

#include "vector.h"
#include <string>

/* Given a drawing of a binary tree, builds that tree and returns a pointer
 * to the root of the tree. Nodes are represented with their numeric data
 * values, with left and right children represented using / and \. For example:
 *
 *              137
 *             /   \
 *            42  199
 *                /  \
 *               /   19
 *              /   /  \
 *             16  3    2
 *
 * Diagonal lines are governed by the rule that they must start within one
 * space of the node they emanate from.
 */
namespace TreeDecoderDetail {
    Node* toTree(const Vector<std::string>& drawing);
}
template <typename... Args>
Node* toTree(Args... args) {
    return TreeDecoderDetail::toTree({ args... });
}

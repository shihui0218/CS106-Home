#include "Nodes.h"
#include "grid.h"
#include "queue.h"
#include "map.h"
#include "set.h"
#include <algorithm>
using namespace std;

namespace {
    /* Returns whether the given character can be a part of a number. */
    bool isNumberChar(char ch) {
        return ch == '-' || isdigit(ch);
    }

    /* Convert a Vector<string> to a uniformly-sized Grid<char>, to make things easier. */
    Grid<char> toGrid(const Vector<string>& drawing) {
        /* Find the longest row. */
        int maxLength = 0;
        for (int row = 0; row < drawing.size(); row++) {
            maxLength = max(maxLength, int(drawing[row].length()));
        }

        /* Make our grid, filling with spaces. */
        Grid<char> result(drawing.size(), maxLength, ' ');

        /* Copy everything over. */
        for (int row = 0; row < drawing.size(); row++) {
            for (int col = 0; col < int(drawing[row].length()); col++) {
                result[row][col] = drawing[row][col];
            }
        }

        return result;
    }

    int readNumber(const Grid<char>& drawing, GridLocation& pos) {
        /* Must be in bounds. */
        if (!drawing.inBounds(pos)) {
            error("Out of bounds.");
        }
        if (!isNumberChar(drawing[pos])) {
            error("readNumber called on a non-number.");
        }

        string number;

        /* Keep reading until we see a non-digit. */
        while (drawing.inBounds(pos.row, pos.col) && isNumberChar(drawing[pos])) {
            number += drawing[pos];
            pos.col++;
        }

        /* Decode the string. */
        return stringToInteger(number);
    }

    /* What items can be in a given place. */
    enum class Type {
        NONE, NODE, LEFT, RIGHT
    };

    /* What's at a location. */
    struct Contents {
        Type type  = Type::NONE;
        Node* node = nullptr; // Either the node itself or what it connects to
    };

    /* Cleans up all nodes allocated in a Grid<Contents>. To avoid multiple
     * deletions, we do this in two passes. The first pass identifies all
     * nodes to delete. The second cleans them up.
     */
    void freeContentNodes(const Grid<Contents>& contents) {
        Set<Node*> toClear;
        for (Contents c: contents) {
            toClear += c.node;
        }

        for (Node* node: toClear) {
            delete node;
        }
    }

    /* Moves to the next spot in the grid, or doesn't do anything
     * if we're past the end.
     */
    template <typename T> GridLocation nextLoc(const Grid<T>& world, GridLocation loc) {
        /* Column overflow? Then go to the next row. */
        if (loc.col >= world.numCols() - 1) {
            loc.col = 0;
            loc.row++;
        } else {
            loc.col++;
        }
        return loc;
    }

    Grid<Contents> decodeDrawing(const Grid<char>& drawing) {
        /* Map from each location to what's there. */
        Grid<Contents> contents(drawing.numRows(), drawing.numCols());

        try {
            /* Translate the grid. */
            for (GridLocation pos = { 0, 0 }; drawing.inBounds(pos); pos = nextLoc(drawing, pos)) {
                /* See what's here. */
                if (drawing[pos] == '/') {
                    contents[pos].type = Type::LEFT;
                } else if (drawing[pos] == '\\') {
                    contents[pos].type = Type::RIGHT;
                } else if (isNumberChar(drawing[pos])) {
                    /* Track where we started. */
                    GridLocation curr = pos;

                    /* Form a new node and read its value. */
                    int value = readNumber(drawing, pos);
                    Node* node = new Node;
                    node->left = node->right = nullptr;
                    node->value = value;

                    /* Stash this in all the right cells. */
                    for (int col = curr.col; col < pos.col; col++) {
                        contents[curr.row][col].type = Type::NODE;
                        contents[curr.row][col].node = node;
                    }

                    /* Because we are going to advance to the next position as part of
                     * the loop, back up one step.
                     */
                    pos.col--;
                } else if (drawing[pos] == ' ') {
                    contents[pos].type = Type::NONE;
                } else {
                    error("Unexpected character.");
                }
            }

            return contents;
        } catch (...) {
            freeContentNodes(contents);
            throw;
        }
    }

    /* Finds the root, or returns an out-of-bounds sentinel if one isn't found. */
    const GridLocation kNone = { -1, -1 };
    GridLocation findRoot(const Grid<Contents>& contents) {
        for (auto loc: contents.locations()) {
            if (contents[loc].type == Type::NODE) {
                return loc;
            } else if (contents[loc].type == Type::LEFT ||
                       contents[loc].type == Type::RIGHT) {
                error("Found connector when looking for root?");
            }
        }
        return kNone;
    }

    /* When we encoutner a node on the BFS, we need to visit all the cells that
     * comprise that node, since it can span multiple cells. This function does
     * that visit, adding in all outgoing links along the way.
     */
    void processNode(const GridLocation& loc,
                  Grid<Contents>& contents,
                  Queue<GridLocation>& worklist,
                  Grid<bool>& visited) {
        /* Scan left. */
        int firstCol = loc.col;
        for (; firstCol >= 0 && contents[loc.row][firstCol].type == Type::NODE; firstCol--) {
            if (visited[loc.row][firstCol]) {
                error("Paths through nodes are not unique.");
            }
            visited[loc.row][firstCol] = true;
        }

        /* Scan right. */
        int lastCol = loc.col + 1;
        for (; lastCol < contents.numCols() && contents[loc.row][lastCol].type == Type::NODE; lastCol++) {
            if (visited[loc.row][lastCol]) {
                error("Paths through nodes are not unique.");
            }
            visited[loc.row][lastCol] = true;
        }

        /* Now look for outgoing links to add. */
        if (loc.row + 1 >= contents.numRows()) {
            return; // Nothing below us
        }

        /* Which links we've seen. */
        bool hasLeft = false;
        bool hasRight = false;

        /* Allow a tolerance of +-1 step. */
        for (int col = firstCol; col <= lastCol; col++) {
            GridLocation next = { loc.row + 1, col };

            /* Don't walk off the grid. */
            if (contents.inBounds(next)) {
                /* It's not possible for this to be visited already, so we
                 * don't need to check for that here.
                 */

                /* Left children can't happen on the blank spot after the node. */
                if (contents[next].type == Type::LEFT && col != lastCol) {
                    if (hasLeft) error("Two left children?");
                    if (hasRight) error("Left child after right?");

                    hasLeft = true;
                    contents[next].node = contents[loc].node;
                    visited[next] = true;
                    worklist.enqueue(next);
                }
                /* Right children can't happen in the blank spot before the node. */
                else if (contents[next].type == Type::RIGHT && col != firstCol - 1) {
                    if (hasRight) error("Two right children?");

                    hasRight = true;
                    contents[next].node = contents[loc].node;
                    visited[next] = true;
                    worklist.enqueue(next);
                }
            }
        }
    }

    struct LinkInfo {
        Node* Node::* link;
        int direction;
    };

    const Map<Type, LinkInfo> kLinks = {
        { Type::LEFT,  { &Node::left,  -1 } },
        { Type::RIGHT, { &Node::right, +1 } }
    };

    /* Continues a link outward, or links it to what it's supposed to connect to. */
    void processLink(GridLocation loc,
                     Type direction,
                     Grid<Contents>& contents,
                     Queue<GridLocation>& worklist,
                     Grid<bool>& visited) {
        /* See what's below us. */
        GridLocation next = { loc.row + 1, loc.col + kLinks[direction].direction };

        /* Bounds-check. */
        if (!contents.inBounds(next)) {
            error("Link extends below tree drawing.");
        }

        /* This must either be a continuation of us or a node. */
        if (contents[next].type == direction) {
            contents[next].node = contents[loc].node;
            visited[next] = true;
            worklist.enqueue(next);
        } else if (contents[next].type == Type::NODE) {
            /* Connect the node. */
            contents[loc].node->*kLinks[direction].link = contents[next].node;

            /* Explore this node. We don't mark things visited here, since if we
             * see this node again in the future it will get marked as a problem.
             */
            worklist.enqueue(next);
        } else {
            error("Connector doesn't reach a node.");
        }
    }
}

Node* TreeDecoderDetail::toTree(const Vector<string>& rawLines) {
    auto contents = decodeDrawing(toGrid(rawLines));

    try {
        Node* root = nullptr;

        /* Find the root node. If one doesn't exist, then there's nothing to see. */
        auto rootLoc = findRoot(contents);
        if (rootLoc == kNone) {
            return nullptr;
        }
        root = contents[rootLoc].node;

        /* Run a BFS over the drawing, making sure that (1) everything is connected
         * back to the root via some path and (2) that we reach everything via a
         * unique path.
         */
        Grid<bool> visited(contents.numRows(), contents.numCols(), false);

        Queue<GridLocation> worklist = { rootLoc };
        while (!worklist.isEmpty()) {
            auto loc = worklist.dequeue();
            if (contents[loc].type == Type::NODE) {
                processNode(loc, contents, worklist, visited);
            } else if (contents[loc].type == Type::LEFT) {
                processLink(loc, Type::LEFT, contents, worklist, visited);
            } else if (contents[loc].type == Type::RIGHT) {
                processLink(loc, Type::RIGHT, contents, worklist, visited);
            } else {
                error("Should not be processing a cell of that type.");
            }
        }

        /* Now, make sure everything was visited. */
        for (auto loc: contents.locations()) {
            if (contents[loc].type != Type::NONE && !visited[loc]) {
                error("Not all locations were visited.");
            }
        }

        return root;
    } catch (...) {
        freeContentNodes(contents);
        throw;
    }
}

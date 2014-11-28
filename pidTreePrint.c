#include <stdio.h>
#include <string.h>

#include "statStuff.h"
#include "pidTree.h"
#include "pidTreePrint.h"


// prints n indentations
void printIndent(int indent)
{
    printf("%*s", indent, " ");
}

// pretty print the statStuff struct 
void printStat(statStuff *stat)
{
    printf("%.*s (%d)", (int)strlen(stat -> comm) - 2, stat -> comm + 1, stat -> pid);
}

// prints pidNode with indentation
void printNode(int indent, pidNode *node)
{
    printIndent(indent);
    printStat(node -> stat);
    printf("\n");
}

void printBranch(int indent, int depth, pidNode *node, int indentWidth, int maxDepth);

// prints all branches children 
void printBranchChildren(int indent, int depth, struct pidNode **nodes, int indentWidth, int maxDepth)
{
    if(maxDepth && depth > maxDepth) return;

    int i = -1;

    while (1)
    {
        i++;

        if (nodes[i] == NULL) break;

        printBranch(indent, depth, nodes[i], indentWidth, maxDepth);
    }
}

// prints the node and recursively prints their children
void printBranch(int indent, int depth, pidNode *node, int indentWidth, int maxDepth)
{
    printNode(indent, node);

    printBranchChildren(indent + indentWidth, depth + 1, node -> children, indentWidth, maxDepth);
}

// prints tree view of nodes by indenting their children
// can specify indentation width and maximum print depth
void printTree(pidNode *node, int indentWidth, int maxDepth)
{
    indentWidth = 0 == indentWidth ? 3 : indentWidth;

    printBranchChildren(0, 0, node -> children, indentWidth, maxDepth);
}
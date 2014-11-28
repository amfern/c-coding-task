#include <stdio.h>
#include <string.h>

#include "statStuff.h"
#include "pidTree.h"
#include "pidTreePrint.h"


void printIndent(int indent)
{
    printf("%*s", indent, " ");
}

void printStat(statStuff *stat)
{
    printf("%.*s (%d)", (int)strlen(stat -> comm) - 2, stat -> comm + 1, stat -> pid);
}

void printNode(int indent, pidNode *node)
{
    printIndent(indent);
    printStat(node -> stat);
    printf("\n");
}

void printBranch(int indent, int depth, pidNode *node, int indentWidth, int maxDepth);

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

void printBranch(int indent, int depth, pidNode *node, int indentWidth, int maxDepth)
{
    printNode(indent, node);

    printBranchChildren(indent + indentWidth, depth + 1, node -> children, indentWidth, maxDepth);
}

void printTree(pidNode *node, int indentWidth, int maxDepth)
{
    printBranchChildren(0, 0, node -> children, indentWidth, maxDepth);
}
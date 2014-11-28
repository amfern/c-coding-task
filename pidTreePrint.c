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

void printBranch(int indent, pidNode *node);

void printBranchChildren(int indent, struct pidNode **nodes)
{

    int i = -1;

    while (1)
    {
        i++;


        if (nodes[i] == NULL) break;

        printBranch(indent, nodes[i]);
    }
}

void printBranch(int indent, pidNode *node)
{
    printNode(indent, node);

    printBranchChildren(indent + 3, node -> children);
}

void printTree(pidNode *node)
{
    printBranchChildren(0, node -> children);
}
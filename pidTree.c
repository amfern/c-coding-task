#include <stdio.h>
#include <stdlib.h>

#include "statStuff.h"
#include "pidTree.h"


// gets all children of specific node by comparing their ppid's to node's pid
void getPidChildren(int pid, statStuff *allStats, statStuff *childrenStats)
{
    int i = -1;
    int ni = -1;

    while (1)
    {
        i++;

        if (!(allStats + i) -> pid) break;

        if (pid != (allStats + i) -> ppid) continue;

        ni++;
        childrenStats[ni] = allStats[i];
    }
}

// populates node.children and their children of children and so on
void makeBranch(pidNode *node, statStuff *allStats)
{
    int i = -1;

    statStuff *ppidStatChildren = (statStuff *)malloc(sizeof(statStuff) * 5000 );
    getPidChildren(node -> stat -> pid, allStats, ppidStatChildren);


    while (1)
    {
        i++;

        if (!ppidStatChildren[i].pid) break;

        pidNode *nextNodeChild = node -> children[i] = malloc(sizeof(pidNode));
        nextNodeChild -> children = malloc(sizeof(pidNode) * 5000);
        nextNodeChild -> stat = &ppidStatChildren[i];

        makeBranch(nextNodeChild, allStats);
    }
}

// makes tree of pidNodes
void makeTree(statStuff *allStats, pidNode *outNode)
{
    outNode -> stat = malloc(sizeof(statStuff));
    outNode -> children = malloc(sizeof(pidNode) * 5000);

    makeBranch(outNode, allStats);
}
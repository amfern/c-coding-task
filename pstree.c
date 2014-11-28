#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "statStuff.h"



typedef struct pidNode {
    statStuff *stat;
    struct pidNode **children;
} pidNode;



void getPidChildren(int pid, statStuff *allStats, statStuff *childrenStats)
{
    int i = -1;
    int ni = -1;

    while (1)
    {
        i++;

        if (!(allStats +i) -> pid) break;

        if (pid != (allStats +i) -> ppid) continue;

        ni++;
        childrenStats[ni] = allStats[i];

        // printf("child: %d\n", childrenStats[ni].pid);
    }
}

void fillNodeChildren(pidNode *node, statStuff *allStats)
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

        // printf("%d\n", nextNodeChild -> stat -> pid);

        fillNodeChildren(nextNodeChild, allStats);
    }
}


void makeTree(statStuff *allStats, pidNode *outNode) {
    outNode -> stat = malloc(sizeof(statStuff));
    outNode -> children = malloc(sizeof(pidNode) * 5000);

    fillNodeChildren(outNode, allStats);
}

int main ()
{
    statStuff *allStats = (statStuff *)malloc(sizeof(statStuff) * 5000);
    pidNode *outNode = malloc(sizeof(pidNode));


    readAllStats(allStats);
    makeTree(allStats, outNode);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "statStuff.h"
#include "pidTree.h"
#include "pidTreePrint.h"

int main ()
{
    statStuff *allStats = (statStuff *)malloc(sizeof(statStuff) * 5000);
    pidNode *outNode = malloc(sizeof(pidNode));

    readAllStats(allStats);
    makeTree(allStats, outNode);
    printTree(outNode);

    return 0;
}
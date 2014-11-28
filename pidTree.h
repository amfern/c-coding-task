typedef struct pidNode {
    statStuff *stat;
    struct pidNode **children;
} pidNode;

void makeTree(statStuff *allStats, pidNode *outNode);
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "statStuff.h"
#include "pidTree.h"
#include "pidTreePrint.h"


typedef struct
{
    int width;
    int depth;
} args;

args parseInputArgs(int argc, char **argv)
{
    args ar = {};
    char *endPtr;
    int c;

    while (1)
    {
        static struct option long_options[] =
        {
            {"width",  optional_argument,       0, 'w'},
            {"depth",  optional_argument,       0, 'd'},
            {0, 0, 0, 0}
        };

        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "w::d::", long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0)
                break;
            printf ("option %s", long_options[option_index].name);
            if (optarg)
                printf (" with arg %s", optarg);
            printf ("\n");
            break;

        case 'w':
            ar.width = strtol(optarg, &endPtr, 10);
            break;

        case 'd':
            ar.depth = strtol(optarg, &endPtr, 10);
            break;

        default:
            abort ();
        }
    }


    return ar;
}



int main (int argc, char **argv)
{
    statStuff *allStats = (statStuff *)malloc(sizeof(statStuff) * 5000);
    pidNode *outNode = malloc(sizeof(pidNode));
    args ar;

    // populate args with user input
    ar = parseInputArgs(argc, argv); 

    // read all pid stat files
    readAllStats(allStats);

    // create tree out of statStuff
    makeTree(allStats, outNode);

    // print the tree to terminal
    printTree(outNode, ar.width, ar.depth);

    // ???
    // prifit

    return 0;
}
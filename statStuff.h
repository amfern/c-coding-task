typedef struct
{
    int pid; // %d
    char comm[256]; // %s
    char state; // %c
    int ppid; // %d
} statStuff;

static const statStuff nullStatStuff;

int readPidMax();

int readAllStats (statStuff *pidStuffs, int pidCount);
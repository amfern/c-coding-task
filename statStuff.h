typedef struct
{
    int pid; // %d
    char comm[256]; // %s
    char state; // %c
    int ppid; // %d
} statStuff;

static const statStuff nullStatStuff;

int readStat (int pid, statStuff *s);

int readAllStats (statStuff *pidStuffs);
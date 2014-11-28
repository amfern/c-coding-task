#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "statStuff.h"


int readStat (int pid, statStuff *s)
{
    FILE *proc;
    char buf[256];
    int ret;
    // printf("%d\n", pid);

    sprintf(buf, "/proc/%d/stat", pid);
    proc = fopen(buf, "r");

    if (!proc) return 1;

    ret = fscanf( proc, "%d %s %c %d", &s -> pid, s -> comm, &s -> state, &s -> ppid );
    fclose(proc);

    return 4 == ret ? 0 : 1;
}

int listDir (char path[], char *list[])
{
    DIR *pathDir;
    struct dirent *dir;
    int i = 0;

    pathDir = opendir(path);

    if (!pathDir) return 1;

    while ((dir = readdir(pathDir)) != NULL)
    {
        list[i] = (char *)malloc(sizeof(char) * 256);
        strcpy(list[i], dir -> d_name);
        i++;
    }
    closedir(pathDir);


    return 0;
}

void filterNumeric (char *strList[], int *numericList)
{
    int i = -1;
    int ni = -1;

    while (1)
    {
        i++;

        if (strList[i] == NULL) break;
        if (!strspn( strList[i], "0123456789" )) continue;

        ni++;
        numericList[ni] = strtol(strList[i], 0, 0);
    }
}

void readStats (int pids[], statStuff *outStats)
{
    int i = -1;
    int ni = -1;

    while (1)
    {
        i++;

        if (!pids[i]) break;

        statStuff *stat = malloc(sizeof(statStuff));
        if (readStat(pids[i], stat)) continue;

        ni++;
        outStats[ni] = *stat;
    }
}

// 2. traverse the statStuffs and pick only the one with existing parent 

int readAllStats (statStuff *pidStuffs)
{
    char **procDirs = (char **)malloc(sizeof(char) * 5000);
    int *procNumerics = (int *)malloc(sizeof(int) * 5000);

    // procDirs[4999] = NULL;
    // pidStuffs[4999] = pidStuffs[0] = nullStatStuff;

    if (listDir("/proc/", procDirs)) return 1;

    filterNumeric(procDirs, procNumerics);
    
    if (-1 == procNumerics[0]) return 1;
    
    readStats(procNumerics, pidStuffs);
    // if (nullStatStuff == pidStuffs[0]) return 1;
    
    // TODO: free **procDirs here
    // TODO: free **procDirs here

    return 0;
}
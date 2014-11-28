#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>

#include "statStuff.h"

// read the maximum pid size
int readPidMax()
{
    FILE *pidMaxFile;
    int ret;

    pidMaxFile = fopen("/proc/sys/kernel/pid_max", "r");

    if (!pidMaxFile) return 1;

    fscanf(pidMaxFile, "%d", &ret);
    fclose(pidMaxFile);

    return ret;
}

// reads the stat file of specifided pid
int readStat (int pid, statStuff *s)
{
    FILE *proc;
    char buf[256];
    int ret;

    sprintf(buf, "/proc/%d/stat", pid);
    proc = fopen(buf, "r");

    if (!proc) return 1;

    ret = fscanf(proc, "%d %s %c %d", &s -> pid, s -> comm, &s -> state, &s -> ppid);
    fclose(proc);

    return 4 == ret ? 0 : 1;
}

// lists all files in a dir
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

// filters to return only numeric values in array
void filterNumeric (char *strList[], int *numericList, int pidCount)
{
    int i = -1;
    int ni = -1;

    while (1)
    {
        i++;

        if (strList[i] == NULL) break;

        if (pidCount == i) break; // incase we reached the allocated limit

        if (!strspn( strList[i], "0123456789" )) continue;

        ni++;
        numericList[ni] = strtol(strList[i], 0, 0);
    }
}

// reads the stats file of pids and returns them in statStuff struct
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

// reads all processes in the system and returns the m in statStuff structs
int readAllStats (statStuff *pidStuffs, int pidCount)
{
    char **procDirs = (char **)malloc(sizeof(char) * INT_MAX);
    int *procNumerics = (int *)malloc(sizeof(int) * pidCount);


    if (listDir("/proc/", procDirs)) return 1;

    filterNumeric(procDirs, procNumerics, pidCount);

    readStats(procNumerics, pidStuffs);

    return 0;
}


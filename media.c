#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

FILE *fptr;
char *fileTypes[] = {".mp4", ".mkv", ".avi", ".3gp", ".flv", ".jpg", "jpeg", ".png", ".psd"};
int sizeOfFileTypes = sizeof fileTypes / sizeof fileTypes[0];

bool endsWith(char* base, char* str) {
    int blen = strlen(base);
    int slen = strlen(str);
    return (blen >= slen) && (0 == strcmp(base + blen - slen, str));
}

bool isMedia(char* str) {
    int i;
    int result = 1;
    for (i=0; i<sizeOfFileTypes; i++) {
        if (endsWith(str, fileTypes[i])) {
            result = 0;
        }
        if (result == 0) {
            return (result == 0);
        }
    }
    return (result == 0);
}

void writeText(char* basePath, char *filePath) {
    if(fptr == NULL)
    {
        printf("Error!");   
        exit(1);             
    }

    fprintf(fptr, "%s/%s\n", basePath, filePath);
}

void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            if (isMedia(dp->d_name)) {
                writeText(basePath, dp->d_name);
                // printf("%s/%s\n", basePath, dp->d_name);
            }

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}

void welcome() {
    int number;
    while (1) {
        printf("1. Run\n2. Exit\n\n");
        printf("> ");
        if (scanf("%d", &number) == 0) {
            fflush(stdin);
            printf("Wrong input!\n");
            continue;
        }

        if ((number <= 0) || (number > 2)) printf("Wrong input!\n");
        else break;
    }
    if (number == 1) {
        printf("Run..");
    }
}

int main() {
    fptr = fopen("log.txt", "a+");

    // listFilesRecursively("C:/GitHub/MediaFinder_C");

    fclose(fptr);
    return 0;
}
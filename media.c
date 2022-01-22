#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

const char *fileTypes[] = {".mp4", ".mkv", ".avi", ".3gp", ".flv", ".jpg", "jpeg", ".png", ".psd"};

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
            printf("%s/%s\n", basePath, dp->d_name);

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}

bool endsWith (char* base, char* str) {
    int blen = strlen(base);
    int slen = strlen(str);
    return (blen >= slen) && (0 == strcmp(base + blen - slen, str));
}

int main() {
   //listFilesRecursively("C:/GitHub/MediaFinder_C");
   //printf("%s\n", endsWith("abc", "c")? "true" : "false");
   return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#ifdef _WIN64
#include <windows.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef linux

#endif

FILE *fptr;
char *allDrives[255] = {};
char *fileTypes[] = {".mp4", ".mkv", ".avi", ".3gp", ".flv", ".jpg", "jpeg", ".png", ".psd"};
int sizeOfFileTypes = sizeof fileTypes / sizeof fileTypes[0];
int fileCount = 0;

char *replace(const char *s, char ch, const char *repl) {
    int count = 0;
    const char *t;
    for(t=s; *t; t++)
        count += (*t == ch);

    size_t rlen = strlen(repl);
    char *res = malloc(strlen(s) + (rlen-1)*count + 1);
    char *ptr = res;
    for(t=s; *t; t++) {
        if(*t == ch) {
            memcpy(ptr, repl, rlen);
            ptr += rlen;
        } else {
            *ptr++ = *t;
        }
    }
    *ptr = 0;
    return res;
}

void createNewFile(char *filename) {

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    assert(strftime(s, sizeof(s), "%c", tm));
    // fprintf(fptr, "\n\n---%s---\n", s);
    printf("%s", tm);

    char *filetype = ".dll";
    char buf[256];
    snprintf(buf, sizeof(buf), "%s%s", filename, filetype);

    fptr = fopen(buf, "a+");
    if(fptr == NULL)
    {
        printf("Error!");   
        exit(1);             
    }
}

void closeFile() {
    fclose(fptr);
}

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
                fileCount++;
                if (fileCount == 1000) {
                    closeFile();
                    //createNewFile();
                }
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

void drive() {
    char buf[255];
    int sz = GetLogicalDriveStrings(sizeof(buf), buf);
    if( sz > 0) {
        char* p1 = buf;
        char* p2;
        int count = 0;
        while(*p1 != '\0' && (p2 = strchr(p1,'\0')) != NULL) {
            allDrives[count] = p1;
            count++;
            p1 = p2+1;
        }
    }
}

int main() {
    // createNewFile("1");

    

    // //drive();

    // listFilesRecursively("C:/GitHub/MediaFinder_C");
    // closeFile();
    return 0;
}
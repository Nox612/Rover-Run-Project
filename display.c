#include <stdio.h>
#include "display.h"

int printMap(char *filename)
{
    FILE *fp = fopen(filename, "r");
    
    if (fp == NULL)
    {
        printf("Error: could not open file %s\n", filename);
        return 1;
    }
    
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }
    printf("\n");

    fclose(fp);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void first()
{
    int dial = 50;
    int count = 0;
    FILE* fp = fopen("in01.txt", "r");
    char c;
    int offset;
    while (fscanf(fp, "%c%d\n", &c, &offset) == 2)
    {
        dial += c == 'L' ? -offset : offset;
        while (dial < 0)
            dial += 100;
        dial = dial % 100;
        if (dial == 0)
            ++count;
    }
    printf("%d\n", count);
    fclose(fp);
}

void second()
{
    int dial = 50;
    int count = 0;
    FILE* fp = fopen("in01.txt", "r");
    char c;
    int offset;
    while (fscanf(fp, "%c%d\n", &c, &offset) == 2)
    {
        do
        {
            int offset_to_use = offset >= 100 ? 100 : offset;
            int new_dial = dial + (c == 'L' ? -offset_to_use : offset_to_use);
            if (dial == 0 || new_dial < 0 || new_dial > 100)
                ++count;
            while (new_dial < 0)
                new_dial += 100;
            dial = new_dial % 100;
            offset -= offset_to_use;
        } while (offset > 0);
    }
    printf("%d\n", count);
    fclose(fp);
}

int main()
{
    second();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int read(long (*ranges)[2])
{
    FILE* fp = fopen("in02.txt", "r");
    int nranges = 0;
    while (fscanf(fp, "%ld-%ld", *ranges, *ranges + 1) == 2)
    {
        ++ranges;
        ++nranges;
        if (fgetc(fp) == EOF)
            break;
    }
    fclose(fp);
    return nranges;
}

int invalid(long x)
{
    long from = 10;
    long split = 10;
    for (int i = 0; i < 5; ++i)
    {
        if (x < from)
            return 0;
        else if (x < from * 10)
            return x / split == x % split;
        from *= 100;
        split *= 10;
    }
    return 0;
}

void first()
{
    long ranges[100][2];
    int nranges = read(ranges);
    long total = 0;
    for (int i = 0; i < nranges; ++i)
        for (long j = ranges[i][0]; j <= ranges[i][1]; ++j)
            if (invalid(j))
                total += j;
    printf("%ld\n", total);
}

int repeated(long x, int single, long factor)
{
    for (long divided = x / factor; divided; divided /= factor)
    {
        if (divided % factor != single)
            return 0;
    }
    return 1;
}

int invalid2(long x)
{
    long factor = 10;
    for (int i = 0; i < 5; ++i, factor *= 10)
    {
        int single = x % factor;
        if (single < factor / 10 || !(x / factor))
            continue;
        else if (repeated(x, single, factor))
            return 1;
    }
    return 0;
}

void second()
{
    long ranges[100][2];
    int nranges = read(ranges);
    long total = 0;
    for (int i = 0; i < nranges; ++i)
        for (long j = ranges[i][0]; j <= ranges[i][1]; ++j)
            if (invalid2(j))
                total += j;
    printf("%ld\n", total);
}

int main()
{
    second();
    return 0;
}
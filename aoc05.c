#include <stdio.h>
#include <stdlib.h>

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

void read(long (**ranges)[2], size_t* nranges, long** numbers, size_t* nnumbers)
{
    FILE* fp = fopen("in05.txt", "r");
    char buf[1024];
    long d1, d2;
    for (*nranges = 0; fscanf(fp, "%ld-%ld\n", &d1, &d2) == 2; ++*nranges)
        ;
    for (*nnumbers = 1; fscanf(fp, "%ld\n", &d1) == 1; ++*nnumbers)
        ;
    fseek(fp, 0, SEEK_SET);
    *ranges = malloc(*nranges * sizeof(long) * 2);
    *numbers = malloc(*nnumbers * sizeof(long));
    for (size_t i = 0; i < *nranges; ++i)
        fscanf(fp, "%ld-%ld\n", &(*ranges)[i][0], &(*ranges)[i][1]);
    for (size_t i = 0; i < *nnumbers; ++i)
        fscanf(fp, "%ld\n", &(*numbers)[i]);
    fclose(fp);
}

void first()
{
    long (*ranges)[2];
    long* numbers;
    size_t nranges, nnumbers;
    read(&ranges, &nranges, &numbers, &nnumbers);
    int total = 0;
    for (size_t i = 0; i < nnumbers; ++i)
        for (size_t j = 0; j < nranges; ++j)
            if (numbers[i] >= ranges[j][0] && numbers[i] <= ranges[j][1])
            {
                ++total;
                break;
            }
    printf("%d\n", total);
    free(ranges);
    free(numbers);
}

int reduce(long (*ranges)[2], size_t nranges)
{
    for (size_t i = 0; i < nranges; ++i)
    {
        if (ranges[i][0] == 0)
            continue;
        for (size_t j = 0; j < nranges; ++j)
        {
            if (j == i || ranges[j][0] == 0)
                continue;
            if (ranges[i][0] <= ranges[j][1] && ranges[i][1] >= ranges[j][0] || ranges[j][0] <= ranges[i][1] && ranges[j][1] >= ranges[i][0])
            {
                ranges[j][0] = min(ranges[i][0], ranges[j][0]);
                ranges[j][1] = max(ranges[i][1], ranges[j][1]);
                ranges[i][0] = ranges[i][1] = 0;
                return 1;
            }
        }
    }
    return 0;
}

void second()
{
    long (*ranges)[2];
    long* numbers;
    size_t nranges, nnumbers;
    read(&ranges, &nranges, &numbers, &nnumbers);
    while (reduce(ranges, nranges))
        ;
    long total = 0;
    for (size_t i = 0; i < nranges; ++i)
        if (ranges[i][0])
            total += ranges[i][1] - ranges[i][0] + 1;
    printf("%ld\n", total);
    free(ranges);
    free(numbers);
}

int main()
{
    second();
    return 0;
}
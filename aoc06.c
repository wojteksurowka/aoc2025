#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void first()
{
    FILE* fp = fopen("in06.txt", "r");
    char buf[20000];
    char *operators = NULL;
    long long* values;
    size_t count;
    while (fgets(buf, sizeof(buf), fp))
    {
        const char* next = strtok(buf, " \n");
        if (operators && !isdigit(*next))
            operators[0] = *next;
        if (next)
        {
            size_t pos;
            for  (pos = 1; (next = strtok(NULL, " \n")) != NULL; ++pos)
                if (operators && !isdigit(*next))
                    operators[pos] = *next;
            if (!operators && pos > 0)
            {
                count = pos;
                operators = malloc(count);
                values = malloc(count * sizeof(long long));
            }
        }
    }
    for (size_t i = 0; i < count; ++i)
        values[i] = operators[i] == '*' ? 1 : 0;
    fseek(fp, 0, SEEK_SET);
    while (fgets(buf, sizeof(buf), fp))
    {
        size_t pos = 0;
        const char* next = strtok(buf, " \n");
        if (next && isdigit(*next))
        {
            if (operators[pos] == '*')
                values[pos] *= atoi(next);
            else
                values[pos] += atoi(next);
            for  (pos = 1; (next = strtok(NULL, " \n")) != NULL; ++pos)
                if (operators[pos] == '*')
                    values[pos] *= atoi(next);
                else
                    values[pos] += atoi(next);
        }
    }
    long long total = 0;
    for (size_t i = 0; i < count; ++i)
        total += values[i];
    printf("%lld\n", total);
    free(operators);
    free(values);
    fclose(fp);
}

void second()
{
    FILE* fp = fopen("in06.txt", "r");
    char buf[5][20000];
    size_t lines = 0;
    while (fgets(buf[lines], sizeof(buf[lines]), fp))
        ++lines;
    long long total = 0;
    char op = 0;
    long long current;
    for (size_t x = 0; buf[0][x] != '\0' && buf[0][x] != '\n'; ++x)
    {
        if (!op)
        {
            op = buf[lines - 1][x];
            current = op == '*' ? 1 : 0;
        }
        char value[10];
        char* ptr = value;
        for (size_t i = 0; i < lines - 1; ++i)
            if (buf[i][x] != ' ')
                *ptr++ = buf[i][x];
        *ptr = 0;
        if (!value[0])
        {
            op = 0;
            total += current;
        }
        else
        {
            if (op == '*')
                current *= atoi(value);
            else
                current += atoi(value);
        }
    }
    total += current;
    printf("%lld\n", total);
    fclose(fp);
}

int main()
{
    second();
    return 0;
}
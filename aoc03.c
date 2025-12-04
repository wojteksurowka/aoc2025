#include <stdio.h>
#include <stdlib.h>

int find(int width)
{
    FILE* fp = fopen("in03.txt", "r");
    char buf[1024];
    long total = 0;
    while (fgets(buf, sizeof(buf), fp) && buf[0] != '\n')
    {
        size_t len = strlen(buf);
        if (buf[len - 1] == '\n')
        {
            buf[len - 1] = 0;
            --len;
        }
        if (!len)
            break;
        long sum = 0;
        char* maxptr = buf;
        for (int i = 0; i < width; ++i)
        {
            for (char* ptr = maxptr + 1; ptr < buf + len - (width - i) + 1; ++ptr)
            {
                if (*ptr > *maxptr)
                {
                    maxptr = ptr;
                }
            }
            sum *= 10;
            sum += *maxptr - '0';
            ++maxptr;
        }
        total += sum;
    }
    printf("%ld\n", total);
    fclose(fp);
}

int first()
{
    find(2);
}

int second()
{
    find(12);
}

int main()
{
    second();
    return 0;
}
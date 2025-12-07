#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read(size_t* width, size_t* height)
{
    FILE* fp = fopen("in07.txt", "r");
    char buf[1024];
    *width = *height = 0;
    while (fgets(buf, sizeof(buf), fp) && buf[0] != '\n')
    {
        if (*width == 0)
        {
            *width = strlen(buf);
            if (buf[*width - 1] == '\n')
                --*width;
            
        }
        ++*height;
    }
    fseek(fp, 0, SEEK_SET);
    char* contents = malloc(*width * *height);
    char* ptr = contents;
    while (fgets(buf, sizeof(buf), fp) && buf[0] != '\n')
    {
        memcpy(ptr, buf, *width);
        ptr += *width;
    }
    fclose(fp);
    return contents;
}

char get(int x, int y, char* contents, size_t width)
{
    return contents[x + y * width];
}

void set(char c, int x, int y, char* contents, size_t width)
{
    contents[x + y * width] = c;
}

size_t find_in_row(size_t y, char c, char* contents, size_t width)
{
    size_t x = 0;
    while (get(x, y, contents, width) != c)
        ++x;
    return x;
}

void count(int* nsplits, long* ntimelines)
{
    size_t width, height;
    char* contents = read(&width, &height);
    size_t* beams = malloc(width * sizeof(size_t));
    beams[0] = find_in_row(0, 'S', contents, width);
    size_t nbeams = 1;
    size_t* timelines = malloc(width * sizeof(size_t));
    memset(timelines, 0, width * sizeof(size_t));
    timelines[beams[0]] = 1;
    *nsplits = 0;
    for (size_t y = 1; y < height; ++y)
    {
        size_t* next_beams = malloc(width * sizeof(size_t));
        size_t next_nbeams = 0;
        size_t* next_timelines = malloc(width * sizeof(size_t));
        memset(next_timelines, 0, width * sizeof(size_t));
        for (size_t b = 0; b < nbeams; ++b)
        {
            char next = get(beams[b], y, contents, width);
            if (next == '^')
            {
                ++*nsplits;
                if (next_nbeams == 0 || next_beams[next_nbeams - 1] < beams[b] - 1)
                {
                    next_beams[next_nbeams++] = beams[b] - 1;
                }
                next_beams[next_nbeams++] = beams[b] + 1;
                next_timelines[beams[b] - 1] += timelines[beams[b]];
                next_timelines[beams[b] + 1] += timelines[beams[b]];
            }
            else
            {
                if (next_nbeams == 0 || next_beams[next_nbeams - 1] < beams[b])
                    next_beams[next_nbeams++] = beams[b];
                next_timelines[beams[b]] += timelines[beams[b]];
            }
        }
        free(timelines);
        free(beams);
        beams = next_beams;
        nbeams = next_nbeams;
        timelines = next_timelines;
    }
    *ntimelines = 0;
    for (size_t i = 0; i < width; ++i)
        *ntimelines += timelines[i];
    free(timelines);
    free(beams);
    free(contents);
}

void first()
{
    int nsplits;
    long ntimelines;
    count(&nsplits, &ntimelines);
    printf("%d\n", nsplits);
}

void second()
{
    int nsplits;
    long ntimelines;
    count(&nsplits, &ntimelines);
    printf("%ld\n", ntimelines);
}

int main()
{
    second();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

char* read(size_t* width, size_t* height)
{
    FILE* fp = fopen("in04.txt", "r");
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

int adjacent(size_t x, size_t y, char* contents, size_t width, size_t height)
{
    int count = 0;
    if (x > 0)
    {
        if (y > 0 && get(x - 1, y - 1, contents, width) == '@')
            ++count;
        if (get(x - 1, y, contents, width) == '@')
            ++count;
        if (y + 1 < height && get(x - 1, y + 1, contents, width) == '@')
            ++count;
    }
    if (y > 0 && get(x, y - 1, contents, width) == '@')
        ++count;
    if (y + 1 < height && get(x, y + 1, contents, width) == '@')
        ++count;
    if (x + 1 < width)
    {
        if (y > 0 && get(x + 1, y - 1, contents, width) == '@')
            ++count;
        if (get(x + 1, y, contents, width) == '@')
            ++count;
        if (y + 1 < height && get(x + 1, y + 1, contents, width) == '@')
            ++count;
    }
    return count;
}

void first()
{
    size_t width, height;
    char* contents = read(&width, &height);
    int total = 0;
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
            if (get(x, y, contents, width) == '@' && adjacent(x, y, contents, width, height) < 4)
                ++total;
    }
    printf("%d\n", total);
    free(contents);
}

int remove_rolls(char* contents, size_t width, size_t height)
{
    int removed = 0;
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
            if (get(x, y, contents, width) == '@' && adjacent(x, y, contents, width, height) < 4)
            {
                set('.', x, y, contents, width);
                ++removed;
            }
    }
    return removed;
}

void second()
{
    size_t width, height;
    char* contents = read(&width, &height);
    int total = 0;
    int removed;
    while ((removed = remove_rolls(contents, width, height)) > 0)
        total += removed;
    printf("%d\n", total);
    free(contents);
}

int main()
{
    second();
    return 0;
}
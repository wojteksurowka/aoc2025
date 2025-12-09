#include <stdio.h>
#include <stdlib.h>

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

struct COORDS
{
    int x, y;
};

struct COORDS* read(size_t* ncoords)
{
    FILE* fp = fopen("in09.txt", "r");
    char buf[1024];
    *ncoords = 0;
    int x, y;
    while (fscanf(fp, "%d,%d", &x, &y) == 2)
    {
        ++*ncoords;
    }
    fseek(fp, 0, SEEK_SET);
    struct COORDS* coords = malloc(*ncoords * sizeof(struct COORDS));
    for (struct COORDS* ptr = coords; fscanf(fp, "%d,%d", &ptr->x, &ptr->y) == 2; ++ptr)
        ;
    fclose(fp);
    return coords;
}

void first()
{
    size_t ncoords;
    struct COORDS* coords = read(&ncoords);
    long long max_area = 0;
    for (size_t i = 0; i < ncoords; ++i)
        for (size_t j = i + 1; j < ncoords; ++j)
        {
            long long area =
                (long long)(max(coords[i].x, coords[j].x) - min(coords[i].x, coords[j].x) + 1) *
                (max(coords[i].y, coords[j].y) - min(coords[i].y, coords[j].y) + 1);
            if (area > max_area)
                max_area = area;
        }
    printf("%lld\n", max_area);
    free(coords);
}

void second()
{
    size_t ncoords;
    struct COORDS* coords = read(&ncoords);
    long long max_area = 0;
    for (size_t i = 0; i < ncoords; ++i)
        for (size_t j = i + 1; j < ncoords; ++j)
        {
            long long x_min = min(coords[i].x, coords[j].x);
            long long x_max = max(coords[i].x, coords[j].x);
            long long y_min = min(coords[i].y, coords[j].y);
            long long y_max = max(coords[i].y, coords[j].y);
            int any_inside = 0;
            for (size_t k = 0; k < ncoords; ++k)
            {
                size_t next = k + 1 < ncoords ? k + 1 : 0;
                if (coords[k].x == coords[next].x)
                {
                    if (x_min < coords[k].x && coords[k].x < x_max)
                    {
                        size_t from = min(coords[k].y, coords[next].y);
                        size_t to = max(coords[k].y, coords[next].y);
                        for (size_t l = from; l <= to; ++l)
                            if (y_min < l && l < y_max)
                            {
                                any_inside = 1;
                                break;
                            }
                    }
                }
                else if (coords[k].y == coords[next].y)
                {
                    if (y_min < coords[k].y && coords[k].y < y_max)
                    {
                        size_t from = min(coords[k].x, coords[next].x);
                        size_t to = max(coords[k].x, coords[next].x);
                        for (size_t l = from; l <= to; ++l)
                            if (x_min < l && l < x_max)
                            {
                                any_inside = 1;
                                break;
                            }
                    }
                }
                if (any_inside)
                    break;
            }
            if (!any_inside)
            {
                long long area = (x_max - x_min + 1) * (y_max - y_min + 1);
                if (area > max_area)
                    max_area = area;
            }
        }
    printf("%lld\n", max_area);
    free(coords);
}

int main()
{
    second();
    return 0;
}
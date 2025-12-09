#include <stdio.h>
#include <stdlib.h>

struct COORDS
{
    int x, y, z;
};

struct COORDS* read(size_t* ncoords)
{
    FILE* fp = fopen("in08.txt", "r");
    char buf[1024];
    *ncoords = 0;
    int x, y, z;
    while (fscanf(fp, "%d,%d,%d", &x, &y, &z) == 3)
    {
        ++*ncoords;
    }
    fseek(fp, 0, SEEK_SET);
    struct COORDS* coords = malloc(*ncoords * sizeof(struct COORDS));
    for (struct COORDS* ptr = coords; fscanf(fp, "%d,%d,%d", &ptr->x, &ptr->y, &ptr->z) == 3; ++ptr)
        ;
    fclose(fp);
    return coords;
}

struct DIST
{
    size_t from, to;
    long long distance;
};

int distance_comparator(struct DIST* left, struct DIST* right)
{
    if (left->distance == right->distance)
    {
        if (left->from == right->from)
            return left->to - right->to;
        else
            return left->from - right->from;
    }
    else
    {
        if (left->distance - right->distance < 0)
            return -1;
        else if  (left->distance - right->distance > 0)
            return 1;
        else
            return 0;
    }
}

struct DIST* distances(struct COORDS* coords, size_t ncoords, size_t* count)
{
    struct DIST* dists = malloc(ncoords * ncoords * sizeof(struct DIST));
    *count = 0;
    for (size_t i = 0; i < ncoords; ++i)
        for (size_t j = i + 1; j < ncoords; ++j)
        {
            dists[*count].from = i;
            dists[*count].to = j;
            dists[*count].distance = (long long)(coords[i].x - coords[j].x) * (long long)(coords[i].x - coords[j].x);
            dists[*count].distance += (long long)(coords[i].y - coords[j].y) * (long long)(coords[i].y - coords[j].y);
            dists[*count].distance += (long long)(coords[i].z - coords[j].z) * (long long)(coords[i].z - coords[j].z);
            ++(*count);
        }
    qsort(dists, *count, sizeof(struct DIST), distance_comparator);
    return dists;
}

int compare_sizes(size_t* left, size_t* right)
{
    if (*left < *right)
        return 1;
    else if (*left > *right)
        return -1;
    else
        return 0;
}

long long result_first(struct DIST* dists, size_t ncoords, size_t npairs, size_t max_connections)
{
    int* groups = malloc(ncoords * sizeof(int));
    for (int i = 0; i < ncoords; ++i)
        groups[i] = -i;
    size_t group = 0;
    for (size_t i = 0; i < npairs; ++i)
    {
        if (groups[dists[i].from] != groups[dists[i].to])
        {
            if (groups[dists[i].from] > 0)
            {
                if (groups[dists[i].to] > 0)
                {
                    int obsolete = groups[dists[i].to];
                    for (size_t g = 1; g <= ncoords; ++g)
                        if (groups[g] == obsolete)
                            groups[g] = groups[dists[i].from];
                }
                else
                    groups[dists[i].to] = groups[dists[i].from];
            }
            else if (groups[dists[i].to] > 0)
                groups[dists[i].from] = groups[dists[i].to];
            else
                groups[dists[i].from] = groups[dists[i].to] = ++group;
        }
        if (--max_connections == 0)
            break;
    }
    long* sizes = malloc((group + 1) * sizeof(long));
    long* ptr = sizes;
    for (size_t g = 1; g <= group; ++g)
    {
        size_t count = 0;
        for (size_t i = 0; i < ncoords; ++i)
            if (groups[i] == g)
                ++count;
        if (count > 0)
            *ptr++ = count;
    }
    qsort(sizes, ptr - sizes, sizeof(size_t), compare_sizes);
    long long product = 1;
    for (size_t i = 0; i < 3; ++i)
        product *= sizes[i];
    free(sizes);
    free(groups);
    return product;
}

long long result_second(struct COORDS* coords, struct DIST* dists, size_t ncoords, size_t npairs)
{
    int* groups = malloc(ncoords * sizeof(int));
    for (int i = 0; i < ncoords; ++i)
        groups[i] = -i;
    size_t group = 0;
    size_t ngroups = 0;
    size_t nsingles = ncoords;
    for (size_t i = 0; i < npairs; ++i)
    {
        if (groups[dists[i].from] != groups[dists[i].to])
        {
            if (groups[dists[i].from] > 0)
            {
                if (groups[dists[i].to] > 0)
                {
                    --ngroups;
                    int obsolete = groups[dists[i].to];
                    for (size_t g = 0; g <= ncoords; ++g)
                        if (groups[g] == obsolete)
                            groups[g] = groups[dists[i].from];
                }
                else
                {
                    groups[dists[i].to] = groups[dists[i].from];
                    --nsingles;
                }
            }
            else if (groups[dists[i].to] > 0)
            {
                groups[dists[i].from] = groups[dists[i].to];
                --nsingles;
            }
            else
            {
                groups[dists[i].from] = groups[dists[i].to] = ++group;
                ++ngroups;
                nsingles -= 2;
            }
        }
        if (ngroups == 1 && nsingles == 0)
        {
            return (long)coords[dists[i].from].x * coords[dists[i].to].x;
        }
    }
    return 0;
}

void first()
{
    size_t ncoords;
    struct COORDS* coords = read(&ncoords);
    size_t npairs;
    struct DIST* dists = distances(coords, ncoords, &npairs);
    long long product = result_first(dists, ncoords, npairs, 1000);
    printf("%lld\n", product);
    free(dists);
    free(coords);
}

void second()
{
    size_t ncoords;
    struct COORDS* coords = read(&ncoords);
    size_t npairs;
    struct DIST* dists = distances(coords, ncoords, &npairs);
    long long product = result_second(coords, dists, ncoords, npairs);
    printf("%lld\n", product);
    free(dists);
    free(coords);
}

int main()
{
    second();
    return 0;
}
#include <cmath>
#include <sys/time.h>
#include "osm.h"

static const int UNROLL_FACTOR = 10;

#define UNUSED(expr) do { (void)(expr); } while (0)


void foo()
{
}

double osm_operation_time(unsigned int iterations)
{
    if (iterations == 0)
    {
        return - 1;
    }
    struct timeval start{}, end{};
    unsigned int k = 0;
    gettimeofday(&start, NULL);
    for (unsigned int i = 0; i < iterations; i += UNROLL_FACTOR)
    {
        k = 1 + 1;
        k = 1 + 1;
        k = 1 + 1;
        k = 1 + 1;
        k = 1 + 1;
        k = 1 + 1;
        k = 1 + 1;
        k = 1 + 1;
        k = 1 + 1;
        k = 1 + 1;
    }
    gettimeofday(&end, NULL);
    UNUSED(k);
    long start_in_microsec = start.tv_sec * 1000000 + start.tv_usec;
    long end_in_microsec = end.tv_sec * 1000000 + end.tv_usec;
    return (double) (end_in_microsec - start_in_microsec) /
           (ceil((double) iterations / UNROLL_FACTOR) *
            UNROLL_FACTOR);
}

double osm_function_time(unsigned int iterations)
{
    if (iterations == 0)
    {
        return - 1;
    }
    struct timeval start{}, end{};
    gettimeofday(&start, NULL);
    for (unsigned int i = 0; i < iterations; i += UNROLL_FACTOR)
    {
        foo();
        foo();
        foo();
        foo();
        foo();
        foo();
        foo();
        foo();
        foo();
        foo();
    }
    gettimeofday(&end, NULL);
    long start_in_microsec = start.tv_sec * 1000000 + start.tv_usec;
    long end_in_microsec = end.tv_sec * 1000000 + end.tv_usec;
    return (double) (end_in_microsec - start_in_microsec) /
           (ceil((double) iterations / UNROLL_FACTOR) *
            UNROLL_FACTOR);
}

double osm_syscall_time(unsigned int iterations)
{
    if (iterations == 0)
    {
        return - 1;
    }
    struct timeval start{}, end{};
    gettimeofday(&start, NULL);
    for (unsigned int i = 0; i < iterations; i += UNROLL_FACTOR)
    {
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
    }
    gettimeofday(&end, NULL);
    long start_in_microsec = start.tv_sec * 1000000 + start.tv_usec;
    long end_in_microsec = end.tv_sec * 1000000 + end.tv_usec;
    return (double) (end_in_microsec - start_in_microsec) /
           (ceil((double) iterations / UNROLL_FACTOR) *
            UNROLL_FACTOR);
}


//
//  main.c
//  Malloc
//
//  Created by linwenhu on 2020/10/29.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "s_malloc_enumerate.h"
#include "s_scalable_zone_statistics.h"

int main(int argc, const char * argv[]) {
    unsigned long long size;
    if ((size = strtoull(argv[1], NULL, 10)) == ULLONG_MAX) {
        fprintf(stderr, "invalid allocate size (%s)\n", argv[1]);
        exit(1);
    }
    
//    enumerate_zone(size);
    enumerate_statistics(size);
    
    return 0;
}

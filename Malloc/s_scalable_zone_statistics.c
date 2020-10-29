//
//  s_scalable_zone_statistics.c
//  Malloc
//
//  Created by linwenhu on 2020/10/29.
//

#include <stdlib.h>
#include <stdio.h>
#include <malloc/malloc.h>

#include "s_nomalloc_printf.h"
#include "s_scalable_zone_statistics.h"

#define PROGRAMNAME "scalable_zone_statitics"

enum { TINY_REGION, SMALL_REGION, LARGER_REGION, HUGE_REGION };

extern boolean_t scalable_zone_statistics(malloc_zone_t *zone, malloc_statistics_t *stats, unsigned subzone);

void print_statistics(const char *label, malloc_statistics_t *stats) {
    nomalloc_printf("%8s%16lu%16lu%16lu", label, stats->blocks_in_use, stats->size_in_use, stats->max_size_in_use);
    
    if (stats->size_allocated != -1) {
        nomalloc_printf("%16lu\n", stats->size_allocated);
    } else {
        printf("%16s\n", "-");
    }
}


void enumerate_statistics(unsigned long long size) {
    void *ptr = NULL;
    malloc_zone_t *zone;
    
    if (!(zone = malloc_default_zone())) {
        exit(1);
    }
    
    if ((ptr = malloc((size_t)size)) == NULL) {
        perror("malloc");
        exit(1);
    }
    
    malloc_zone_print(NULL, 0);
//    zone->introspect->print(zone, 0);
    
    /* scalable_zone_statistics access invalid memory
        malloc_statistics_t stats;
        nomalloc_printf("%8s%16s%16s%16s%16s\n", "Region", "Block in use", "Size in use", "Max size in use", "Size allocated");
        scalable_zone_statistics(zone, &stats, TINY_REGION);
        print_statistics("tiny", &stats);
        
        scalable_zone_statistics(zone, &stats, SMALL_REGION);
        print_statistics("small", &stats);
        
        scalable_zone_statistics(zone, &stats, LARGER_REGION);
        stats.size_allocated = -1;
        print_statistics("large", &stats);
        
        scalable_zone_statistics(zone, &stats, HUGE_REGION);
        stats.size_allocated = -1;
        print_statistics("huge", &stats);
    
     */
    if (ptr) {
        free(ptr);
    }
}

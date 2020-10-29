//
//  s_malloc_intercept.c
//  Malloc
//
//  Created by linwenhu on 2020/10/29.
//

#include <stdlib.h>
#include <unistd.h>
#include <malloc/malloc.h>

#include "s_malloc_intercept.h"
#include "s_nomalloc_printf.h"

void *(*system_malloc)(malloc_zone_t *zone, size_t size);
void (*system_free)(malloc_zone_t *zone, void *ptr);

void *my_malloc(malloc_zone_t *zone, size_t size) {
    void *ptr = system_malloc(zone, size);
    
    nomalloc_printf("%p = malloc(zone=%p, size=%lu)\n", ptr, zone, size);
    return  ptr;
}

void my_free(malloc_zone_t *zone, void *ptr) {
    nomalloc_printf("free(zone=%p, ptr=%p)\n", zone, ptr);
    system_free(zone, ptr);
}

void setup_intercept(void) {
    malloc_zone_t *zone = malloc_default_zone();
    system_malloc = zone->malloc;
    system_free = zone->free;
    
    zone->malloc = my_malloc;
    zone->free = my_free;
}


void malloc_intercept_run(void) {
    setup_intercept();
    
    free(malloc(1234));
}

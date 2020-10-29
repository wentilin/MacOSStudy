//
//  s_malloc_enumerate.c
//  Malloc
//
//  Created by linwenhu on 2020/10/28.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc/malloc.h>
#include <mach/mach.h>

#include "s_nomalloc_printf.h"
#include "s_malloc_enumerate.h"

struct recorder_args {
    const char *label;
    unsigned type_mask;
} recorder_args[] = {
    { "Allocated pointers\n", MALLOC_PTR_IN_USE_RANGE_TYPE },
    { "\nRegions containing pointers\n", MALLOC_PTR_REGION_RANGE_TYPE },
    { "\nInternal regions\n", MALLOC_ADMIN_REGION_RANGE_TYPE }
};

void my_vm_range_recorder(task_t task, void *context, unsigned type_mask, vm_range_t *ranges, unsigned range_count) {
    vm_range_t *r, *end;
    for (r = ranges, end = ranges + range_count; r < end; r++) {
        nomalloc_printf("%16p   %u\n", r->address, r->size);
    }
}

void enumerate_zone(unsigned long long size) {
    int i;
    void *ptr = NULL;
    malloc_zone_t *zone;
    
    if (!(zone = malloc_default_zone())) {
        exit(1);
    }
    
    if ((ptr = malloc((size_t)size)) == NULL) {
        perror("malloc");
        exit(1);
    }
    
    for (i = 0; i < sizeof(recorder_args)/sizeof(struct recorder_args); i++) {
        nomalloc_printf("%s      address     bytes\n", recorder_args[i].label);
        zone->introspect->enumerator(mach_task_self(),
                                     NULL,
                                     recorder_args[i].type_mask,
                                     (vm_address_t)zone,
                                     NULL,
                                     my_vm_range_recorder);
    }
}

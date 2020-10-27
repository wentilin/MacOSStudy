//
//  s_vm_inherit.c
//  MacOSStudy
//
//  Created by linwenhu on 2020/10/27.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach/task.h>
#include <mach/mach.h>
#include <mach/mach_vm.h>

#include "s_vm_inherit.h"

#define OUT_ON_MACH_ERROR(msg, retval) \
if (kr != KERN_SUCCESS) { mach_error(msg ":", kr); goto out; }

#define FIRST_UINT32(addr) (*((uint32_t *)addr))

static mach_vm_address_t page_shared;
static mach_vm_address_t page_cow;

kern_return_t get_object_id(mach_vm_address_t offset, int *obj_id, int *ref_count) {
    kern_return_t kr;
    mach_port_t unused;
    mach_vm_size_t size = (mach_vm_size_t)vm_page_size;
    mach_vm_address_t address = offset;

    vm_region_top_info_data_t info;
    mach_msg_type_number_t count = VM_REGION_TOP_INFO_COUNT;
    
    kr = mach_vm_region(mach_task_self(), &address, &size, VM_REGION_TOP_INFO, (vm_region_info_t)&info, &count, &unused);
    
    if (kr == KERN_SUCCESS) {
        *obj_id = info.obj_id;
        *ref_count = info.ref_count;
    }
    
    return kr;
}

void peek_at_some_memory(const char *who, const char *msg) {
    int obj_id, ref_count;
    kern_return_t kr;
    
    kr = get_object_id(page_shared, &obj_id, &ref_count);
    printf("%-12s%-8s%-10x%-12x%-10d%s\n", who, "SHARED", FIRST_UINT32(page_shared), obj_id, ref_count, msg);
    
    kr = get_object_id(page_cow, &obj_id, &ref_count);
    printf("%-12s%-8s%-10x%-12x%-10d%s\n", who, "COW", FIRST_UINT32(page_cow), obj_id, ref_count, msg);
}

void child_process(void) {
    peek_at_some_memory("child", "before touching any memeory");
    FIRST_UINT32(page_shared) = (unsigned int)0xFEEDF00D;
    FIRST_UINT32(page_cow) = (unsigned int)0xBADDF00D;
    peek_at_some_memory("child", "after writing to memory");
    
    exit(0);
}


void s_vm_inherit_run(void) {
    kern_return_t kr;
    int status;
    mach_port_t mytask = mach_task_self();
    mach_vm_size_t size = (mach_vm_size_t)vm_page_size;
    
    kr = mach_vm_allocate(mytask, &page_shared, size, VM_FLAGS_ANYWHERE);
    OUT_ON_MACH_ERROR("vm_alloc", kr);
    mach_vm_inherit(mytask, page_shared, size, VM_INHERIT_SHARE);
    OUT_ON_MACH_ERROR("vm_inherit(VM_INHERIT_SHARE)", kr);
    
    kr = mach_vm_allocate(mytask, &page_cow, size, VM_FLAGS_ANYWHERE);
    OUT_ON_MACH_ERROR("vm_alloc", kr);
    mach_vm_inherit(mytask, page_cow, size, VM_INHERIT_COPY);
    OUT_ON_MACH_ERROR("vm_inherit(VM_INHERIT_COPY)", kr);
    
    FIRST_UINT32(page_shared) = (unsigned int)0xAAAAAAAA;
    FIRST_UINT32(page_cow) = (unsigned int)0xBBBBBBBB;
    
    printf("%-12s%-8s%-10s%-12s%-10s%s\n", "Process", "Page", "Contents", "VM Object", "Refcount", "Event");
    
    peek_at_some_memory("parent", "before forking");
    
    if (fork()) {
        child_process();
    }
    
    wait(&status);
    
    peek_at_some_memory("parent", "after child is done");
out:
    mach_vm_deallocate(mytask, page_shared, size);
    mach_vm_deallocate(mytask, page_cow, size);
    exit(0);
}

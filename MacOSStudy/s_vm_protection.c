//
//  s_vm_protection.c
//  MacOSStudy
//
//  Created by linwenhu on 2020/10/27.
//

#include "s_vm_protection.h"
#include "s_common.h"

void s_vm_protection_run(void) {
    char *ptr;
    kern_return_t kr;
    mach_vm_address_t a_page = (mach_vm_address_t)0;
    mach_vm_size_t size = (mach_vm_size_t)vm_page_size;
    
    kr = mach_vm_allocate(mach_task_self(), &a_page, size, VM_FLAGS_ANYWHERE);
    OUT_ON_MACH_ERROR("vm_alloc", kr);
    
    ptr = (char *)a_page + 2048;
    
    snprintf(ptr, (size_t)16, "Hello, mach!");
    
    kr = mach_vm_protect(mach_task_self(), a_page, size, 4, VM_PROT_NONE);
    OUT_ON_MACH_ERROR("vm_protect", kr);
    
    printf("%s\n", ptr);
out:
    if (a_page) {
        mach_vm_deallocate(mach_task_self(), a_page, size);
    }
    exit(kr);
}

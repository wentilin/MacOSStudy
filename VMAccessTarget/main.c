//
//  main.c
//  VMAccessTarget
//
//  Created by linwenhu on 2020/10/27.
//

#include "s_common.h"

#define SOME_CHAR 'A'

int main(int argc, const char * argv[]) {
    kern_return_t kr;
    mach_vm_address_t address;
    mach_vm_size_t size = (mach_vm_size_t)vm_page_size;
    
    kr = mach_vm_allocate(mach_task_self(), &address, size, VM_FLAGS_ANYWHERE);
    if (kr != KERN_SUCCESS) {
        mach_error("vm_alloc:", kr);
        exit(1);
    }
    
    memset((char *)address, SOME_CHAR, vm_page_size);
    
    printf("pid=%d, address=%p\n", getpid(), (void *)address);
    
    while ((*(char *)address) == SOME_CHAR);
    
    mach_vm_deallocate(mach_task_self(), address, size);
    
    return 0;
}

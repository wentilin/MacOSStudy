//
//  main.c
//  MacOSStudy
//
//  Created by linwenhu on 2020/10/27.
//

#include <stdio.h>
#include "s_vm_inherit.h"
#include "s_vm_protection.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
//    s_vm_inherit_run();
    
    // bus error
    s_vm_protection_run();
    
    return 0;
}

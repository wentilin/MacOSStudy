//
//  s_common.h
//  MacOSStudy
//
//  Created by linwenhu on 2020/10/27.
//

#ifndef s_common_h
#define s_common_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach/task.h>
#include <mach/mach.h>
#include <mach/mach_vm.h>

#define OUT_ON_MACH_ERROR(msg, retval) \
if (kr != KERN_SUCCESS) { mach_error(msg ":", kr); goto out; }

#define FIRST_UINT32(addr) (*((uint32_t *)addr))

#endif /* s_common_h */

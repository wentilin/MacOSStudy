//
//  s_shm_ipc_header.h
//  MacOSStudy
//
//  Created by linwenhu on 2020/10/27.
//

#ifndef s_shm_ipc_header_h
#define s_shm_ipc_header_h

#include "s_common.h"

#include <servers/bootstrap.h>

#define SERVER_NAME "com.macosstudy.SHMServer"
#define SHM_MSG_ID 400

typedef struct {
    mach_msg_header_t header;
} msg_format_request_t;

typedef struct {
    mach_msg_header_t header;
    mach_msg_trailer_t trailer;
} msg_format_request_r_t;

typedef struct {
    mach_msg_header_t header;
    mach_msg_body_t body;
    mach_msg_port_descriptor_t data;
} msg_format_response_t;

typedef struct {
    mach_msg_header_t header;
    mach_msg_body_t body;
    mach_msg_port_descriptor_t data;
    mach_msg_trailer_t trailer;
} msg_format_response_r_t;

#endif /* s_shm_ipc_header_h */

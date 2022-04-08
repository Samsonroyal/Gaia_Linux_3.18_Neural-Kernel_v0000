/*
 * Include file for the interface to IST BIOS
 */
#ifndef _UAPI_ASM_X86_IST_H
#define _UAPI_ASM_X86_IST_H



#include <linux/types.h>

struct ist_info {
	__u32 signature;
	__u32 command;
	__u32 event;
	__u32 perf_level;
};

#endif /* _UAPI_ASM_X86_IST_H */
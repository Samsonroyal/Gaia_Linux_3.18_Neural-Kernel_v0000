/* Generic MTRR (Memory Type Range Register) ioctls. */
#ifndef _UAPI_ASM_X86_MTRR_H
#define _UAPI_ASM_X86_MTRR_H

#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/errno.h>

#define	MTRR_IOCTL_BASE	'M'

/* Warning: this structure has a different order from i386
   on x86-64. The 32bit emulation code takes care of that.
   But you need to use this for 64bit, otherwise your X server
   will break. */

#ifdef __i386__
struct mtrr_sentry {
    unsigned long base;    /*  Base address     */
    unsigned int size;    /*  Size of region   */
    unsigned int type;     /*  Type of region   */
};

struct mtrr_gentry {
    unsigned int regnum;   /*  Register number  */
    unsigned long base;    /*  Base address     */
    unsigned int size;    /*  Size of region   */
    unsigned int type;     /*  Type of region   */
};

#else /* __i386__ */

struct mtrr_sentry {
	__u64 base;		/*  Base address     */
	__u32 size;		/*  Size of region   */
	__u32 type;		/*  Type of region   */
};

struct mtrr_gentry {
	__u64 base;		/*  Base address     */
	__u32 size;		/*  Size of region   */
	__u32 regnum;		/*  Register number  */
	__u32 type;		/*  Type of region   */
	__u32 _pad;		/*  Unused	     */
};

#endif /* !__i386__ */

struct mtrr_var_range {
	__u32 base_lo;
	__u32 base_hi;
	__u32 mask_lo;
	__u32 mask_hi;
};

/* In the Intel processor's MTRR interface, the MTRR type is always held in
   an 8 bit field: */
typedef __u8 mtrr_type;

#define MTRR_NUM_FIXED_RANGES 88
#define MTRR_MAX_VAR_RANGES 256

struct mtrr_state_type {
	struct mtrr_var_range var_ranges[MTRR_MAX_VAR_RANGES];
	mtrr_type fixed_ranges[MTRR_NUM_FIXED_RANGES];
	unsigned char enabled;
	unsigned char have_fixed;
	mtrr_type def_type;
};

#define MTRRphysBase_MSR(reg) (0x200 + 2 * (reg))
#define MTRRphysMask_MSR(reg) (0x200 + 2 * (reg) + 1)

/*  These are the various ioctls  */
#define MTRRIOC_ADD_ENTRY        _IOW(MTRR_IOCTL_BASE,  0, struct mtrr_sentry)
#define MTRRIOC_SET_ENTRY        _IOW(MTRR_IOCTL_BASE,  1, struct mtrr_sentry)
#define MTRRIOC_DEL_ENTRY        _IOW(MTRR_IOCTL_BASE,  2, struct mtrr_sentry)
#define MTRRIOC_GET_ENTRY        _IOWR(MTRR_IOCTL_BASE, 3, struct mtrr_gentry)
#define MTRRIOC_KILL_ENTRY       _IOW(MTRR_IOCTL_BASE,  4, struct mtrr_sentry)
#define MTRRIOC_ADD_PAGE_ENTRY   _IOW(MTRR_IOCTL_BASE,  5, struct mtrr_sentry)
#define MTRRIOC_SET_PAGE_ENTRY   _IOW(MTRR_IOCTL_BASE,  6, struct mtrr_sentry)
#define MTRRIOC_DEL_PAGE_ENTRY   _IOW(MTRR_IOCTL_BASE,  7, struct mtrr_sentry)
#define MTRRIOC_GET_PAGE_ENTRY   _IOWR(MTRR_IOCTL_BASE, 8, struct mtrr_gentry)
#define MTRRIOC_KILL_PAGE_ENTRY  _IOW(MTRR_IOCTL_BASE,  9, struct mtrr_sentry)

/*  These are the region types  */
#define MTRR_TYPE_UNCACHABLE 0
#define MTRR_TYPE_WRCOMB     1
/*#define MTRR_TYPE_         2*/
/*#define MTRR_TYPE_         3*/
#define MTRR_TYPE_WRTHROUGH  4
#define MTRR_TYPE_WRPROT     5
#define MTRR_TYPE_WRBACK     6
#define MTRR_NUM_TYPES       7


#endif /* _UAPI_ASM_X86_MTRR_H */

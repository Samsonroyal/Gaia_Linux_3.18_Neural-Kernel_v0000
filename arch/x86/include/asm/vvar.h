/*
 * vvar.h: Shared vDSO/kernel variable declarations
 */

#ifndef _ASM_X86_VVAR_H
#define _ASM_X86_VVAR_H

#if defined(__VVAR_KERNEL_LDS)

/* The kernel linker script defines its own magic to put vvars in the
 * right place.
 */
#define DECLARE_VVAR(offset, type, name) \
	EMIT_VVAR(name, offset)

#else

extern char __vvar_page;

#define DECLARE_VVAR(offset, type, name)				\
	extern type vvar_ ## name __attribute__((visibility("hidden")));

#define VVAR(name) (vvar_ ## name)

#define DEFINE_VVAR(type, name)						\
	type name							\
	__attribute__((section(".vvar_" #name), aligned(16))) __visible

#endif

/* DECLARE_VVAR(offset, type, name) */

DECLARE_VVAR(0, volatile unsigned long, jiffies)
DECLARE_VVAR(16, int, vgetcpu_mode)
DECLARE_VVAR(128, struct vsyscall_gtod_data, vsyscall_gtod_data)

#undef DECLARE_VVAR

#endif

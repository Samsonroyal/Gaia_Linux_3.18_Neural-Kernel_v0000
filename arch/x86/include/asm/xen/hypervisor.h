/*
 * Linux-specific hypervisor handling.
 */

#ifndef _ASM_X86_XEN_HYPERVISOR_H
#define _ASM_X86_XEN_HYPERVISOR_H

extern struct shared_info *HYPERVISOR_shared_info;
extern struct start_info *xen_start_info;

#include <asm/processor.h>

static inline uint32_t xen_cpuid_base(void)
{
	return hypervisor_cpuid_base("XenVMMXenVMM", 2);
}

#ifdef CONFIG_XEN
extern bool xen_hvm_need_lapic(void);

static inline bool xen_x2apic_para_available(void)
{
	return xen_hvm_need_lapic();
}
#else
static inline bool xen_x2apic_para_available(void)
{
	return (xen_cpuid_base() != 0);
}
#endif

#endif /* _ASM_X86_XEN_HYPERVISOR_H */

#ifndef _ASM_X86_HYPERVISOR_H
#define _ASM_X86_HYPERVISOR_H

#ifdef CONFIG_HYPERVISOR_GUEST

#include <asm/kvm_para.h>
#include <asm/xen/hypervisor.h>

/*
 * x86 hypervisor information
 */
struct hypervisor_x86 {
	/* Hypervisor name */
	const char	*name;

	/* Detection routine */
	uint32_t	(*detect)(void);

	/* Adjust CPU feature bits (run once per CPU) */
	void		(*set_cpu_features)(struct cpuinfo_x86 *);

	/* Platform setup (run once per boot) */
	void		(*init_platform)(void);

	/* X2APIC detection (run once per boot) */
	bool		(*x2apic_available)(void);
};

extern const struct hypervisor_x86 *x86_hyper;

/* Recognized hypervisors */
extern const struct hypervisor_x86 x86_hyper_vmware;
extern const struct hypervisor_x86 x86_hyper_ms_hyperv;
extern const struct hypervisor_x86 x86_hyper_xen_hvm;
extern const struct hypervisor_x86 x86_hyper_kvm;

extern void init_hypervisor(struct cpuinfo_x86 *c);
extern void init_hypervisor_platform(void);
extern bool hypervisor_x2apic_available(void);
#else
static inline void init_hypervisor(struct cpuinfo_x86 *c) { }
static inline void init_hypervisor_platform(void) { }
static inline bool hypervisor_x2apic_available(void) { return false; }
#endif /* CONFIG_HYPERVISOR_GUEST */
#endif /* _ASM_X86_HYPERVISOR_H */

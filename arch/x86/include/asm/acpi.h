#ifndef _ASM_X86_ACPI_H
#define _ASM_X86_ACPI_H

#include <acpi/pdc_intel.h>

#include <asm/numa.h>
#include <asm/fixmap.h>
#include <asm/processor.h>
#include <asm/mmu.h>
#include <asm/mpspec.h>
#include <asm/realmode.h>

#ifdef CONFIG_ACPI
extern int acpi_lapic;
extern int acpi_ioapic;
extern int acpi_noirq;
extern int acpi_strict;
extern int acpi_disabled;
extern int acpi_pci_disabled;
extern int acpi_skip_timer_override;
extern int acpi_use_timer_override;
extern int acpi_fix_pin2_polarity;
extern int acpi_disable_cmcff;

extern u8 acpi_sci_flags;
extern int acpi_sci_override_gsi;
void acpi_pic_sci_set_trigger(unsigned int, u16);

extern int (*__acpi_register_gsi)(struct device *dev, u32 gsi,
				  int trigger, int polarity);

static inline void disable_acpi(void)
{
	acpi_disabled = 1;
	acpi_pci_disabled = 1;
	acpi_noirq = 1;
}

extern int acpi_gsi_to_irq(u32 gsi, unsigned int *irq);

static inline void acpi_noirq_set(void) { acpi_noirq = 1; }
static inline void acpi_disable_pci(void)
{
	acpi_pci_disabled = 1;
	acpi_noirq_set();
}

/* Low-level suspend routine. */
extern int (*acpi_suspend_lowlevel)(void);

/* Physical address to resume after wakeup */
#define acpi_wakeup_address ((unsigned long)(real_mode_header->wakeup_start))

/*
 * Check if the CPU can handle C2 and deeper
 */
static inline unsigned int acpi_processor_cstate_check(unsigned int max_cstate)
{
	/*
	 * Early models (<=5) of AMD Opterons are not supposed to go into
	 * C2 state.
	 *
	 * Steppings 0x0A and later are good
	 */
	if (boot_cpu_data.x86 == 0x0F &&
	    boot_cpu_data.x86_vendor == X86_VENDOR_AMD &&
	    boot_cpu_data.x86_model <= 0x05 &&
	    boot_cpu_data.x86_mask < 0x0A)
		return 1;
	else if (amd_e400_c1e_detected)
		return 1;
	else
		return max_cstate;
}

static inline bool arch_has_acpi_pdc(void)
{
	struct cpuinfo_x86 *c = &cpu_data(0);
	return (c->x86_vendor == X86_VENDOR_INTEL ||
		c->x86_vendor == X86_VENDOR_CENTAUR);
}

static inline void arch_acpi_set_pdc_bits(u32 *buf)
{
	struct cpuinfo_x86 *c = &cpu_data(0);

	buf[2] |= ACPI_PDC_C_CAPABILITY_SMP;

	if (cpu_has(c, X86_FEATURE_EST))
		buf[2] |= ACPI_PDC_EST_CAPABILITY_SWSMP;

	if (cpu_has(c, X86_FEATURE_ACPI))
		buf[2] |= ACPI_PDC_T_FFH;

	/*
	 * If mwait/monitor is unsupported, C2/C3_FFH will be disabled
	 */
	if (!cpu_has(c, X86_FEATURE_MWAIT))
		buf[2] &= ~(ACPI_PDC_C_C2C3_FFH);
}

static inline bool acpi_has_cpu_in_madt(void)
{
	return !!acpi_lapic;
}

#else /* !CONFIG_ACPI */

#define acpi_lapic 0
#define acpi_ioapic 0
#define acpi_disable_cmcff 0
static inline void acpi_noirq_set(void) { }
static inline void acpi_disable_pci(void) { }
static inline void disable_acpi(void) { }

#endif /* !CONFIG_ACPI */

#define ARCH_HAS_POWER_INIT	1

#ifdef CONFIG_ACPI_NUMA
extern int acpi_numa;
extern int x86_acpi_numa_init(void);
#endif /* CONFIG_ACPI_NUMA */

#define acpi_unlazy_tlb(x)	leave_mm(x)

#endif /* _ASM_X86_ACPI_H */

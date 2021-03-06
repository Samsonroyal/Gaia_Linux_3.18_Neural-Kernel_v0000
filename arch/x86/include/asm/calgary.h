/*
 * Derived from include/asm-powerpc/iommu.h
 */

#ifndef _ASM_X86_CALGARY_H
#define _ASM_X86_CALGARY_H

#include <linux/spinlock.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/timer.h>
#include <asm/types.h>

struct iommu_table {
	struct cal_chipset_ops *chip_ops; /* chipset specific funcs */
	unsigned long  it_base;      /* mapped address of tce table */
	unsigned long  it_hint;      /* Hint for next alloc */
	unsigned long *it_map;       /* A simple allocation bitmap for now */
	void __iomem  *bbar;         /* Bridge BAR */
	u64	       tar_val;      /* Table Address Register */
	struct timer_list watchdog_timer;
	spinlock_t     it_lock;      /* Protects it_map */
	unsigned int   it_size;      /* Size of iommu table in entries */
	unsigned char  it_busno;     /* Bus number this table belongs to */
};

struct cal_chipset_ops {
	void (*handle_quirks)(struct iommu_table *tbl, struct pci_dev *dev);
	void (*tce_cache_blast)(struct iommu_table *tbl);
	void (*dump_error_regs)(struct iommu_table *tbl);
};

#define TCE_TABLE_SIZE_UNSPECIFIED	~0
#define TCE_TABLE_SIZE_64K		0
#define TCE_TABLE_SIZE_128K		1
#define TCE_TABLE_SIZE_256K		2
#define TCE_TABLE_SIZE_512K		3
#define TCE_TABLE_SIZE_1M		4
#define TCE_TABLE_SIZE_2M		5
#define TCE_TABLE_SIZE_4M		6
#define TCE_TABLE_SIZE_8M		7

extern int use_calgary;

#ifdef CONFIG_CALGARY_IOMMU
extern int detect_calgary(void);
#else
static inline int detect_calgary(void) { return -ENODEV; }
#endif

#endif /* _ASM_X86_CALGARY_H */

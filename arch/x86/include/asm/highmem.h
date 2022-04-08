/*
 * highmem.h: virtual kernel memory mappings for high memory
 *
 * Used in CONFIG_HIGHMEM systems for memory pages which
 * are not addressable by direct kernel virtual addresses.
 *
 */

#ifndef _ASM_X86_HIGHMEM_H
#define _ASM_X86_HIGHMEM_H

#ifdef __KERNEL__

#include <linux/interrupt.h>
#include <linux/threads.h>
#include <asm/kmap_types.h>
#include <asm/tlbflush.h>
#include <asm/paravirt.h>
#include <asm/fixmap.h>

/* declarations for highmem.c */
extern unsigned long highstart_pfn, highend_pfn;

/*
 * Right now we initialize only a single pte table. It can be extended
 * easily, subsequent pte tables have to be allocated in one physical
 * chunk of RAM.
 */
/*
 * Ordering is:
 *
 * FIXADDR_TOP
 * 			fixed_addresses
 * FIXADDR_START
 * 			temp fixed addresses
 * FIXADDR_BOOT_START
 * 			Persistent kmap area
 * PKMAP_BASE
 * VMALLOC_END
 * 			Vmalloc area
 * VMALLOC_START
 * high_memory
 */
#define LAST_PKMAP_MASK (LAST_PKMAP-1)
#define PKMAP_NR(virt)  ((virt-PKMAP_BASE) >> PAGE_SHIFT)
#define PKMAP_ADDR(nr)  (PKMAP_BASE + ((nr) << PAGE_SHIFT))

extern void *kmap_high(struct page *page);
extern void kunmap_high(struct page *page);

void *kmap(struct page *page);
void kunmap(struct page *page);

void *kmap_atomic_prot(struct page *page, pgprot_t prot);
void *kmap_atomic(struct page *page);
void __kunmap_atomic(void *kvaddr);
void *kmap_atomic_pfn(unsigned long pfn);
void *kmap_atomic_prot_pfn(unsigned long pfn, pgprot_t prot);
struct page *kmap_atomic_to_page(void *ptr);

#define flush_cache_kmaps()	do { } while (0)

extern void add_highpages_with_active_regions(int nid, unsigned long start_pfn,
					unsigned long end_pfn);

#endif /* __KERNEL__ */

#endif /* _ASM_X86_HIGHMEM_H */

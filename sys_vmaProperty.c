#include <linux/kernel.h>
#include <linux/sched.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <linux/mm_types.h>

asmlinkage int sys_vmaProperty(unsigned long mem, int processID)
{
        struct task_struct *task = find_task_by_vpid(processID);
        struct mm_struct *memory = task->active_mm;
    
        // flags for page table entries
        int data = 0;
        int reference = 0;
        int dirty = 0;
    
        /* sets up page global directory, page upper directory, page middle directory,
         and page table entry pointer
         page global directory
         page upper directory
         page middle directory
         page table entry pointer
         page table entry */
        pgd_t *pgd = pgd_offset(memory, mem);
        pud_t *pud = pud_offset(pgd, mem);
        pmd_t *pmd = pmd_offset(pud, mem);
        pte_t *ptep = pte_offset_kernel(pmd, mem);
        pte_t pte = *ptep;
        data = pte_present(pte);
    
        // prints flags associated with page table entry
        printk("Present flag: %i\n", data?1:0);
        reference = pageTableEntry_young(pageTableEntry);
        printk("Referenced flag: %i\n", ref?1:0);
        dirty = pageTableEntry_dirty(pageTableEntry);
        printk("Dirty flag: %i\n", dirty?1:0);
        return 0;
}

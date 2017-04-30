#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/fs.h>
#include <asm/page.h>
#include <asm/mman.h>

asmlinkage int sys_vmaStatistic(int processID)
{
        struct task_struct *thisTask;
        struct mm_struct *thisMem;
        struct vm_area_struct *allVmas;
        struct vm_area_struct thisVma;

        unsigned long protection=0;
        unsigned long start=0;
    
        int numVMAS;
        int totalSize=0;
        int count=0;
    
        // mapped file name
        char *fileName;

        // connect variables
        thisTask = find_task_by_vpid(pid);
        thisMem = thisTask->active_mm;
        allVmas = thisMem->mmap;
        numVMAS = thisMem->map_count;
        thisVMA = *all_vmas;
        start=thisVMA.vm_start;

        // print total number of VMAS currently running
        printk("\nThere are currently %i VMAs.\n", numVMAS);
    
        // print info about each VMA in total number of VMAS
        for (thisVMA = *allVmas; count < numVMAS; count++)
        {
                printk("***************************************************\n");
                printk("VMA #%i:\n", count+1);

                printk("Start address: 0x%lx\n", thisVMA.vm_start);
                printk("End address: 0x%lx\n", thisVMA.vm_end);
                printk("Total size (End - Start): %lu\n", thisVMA.vm_end - thisVMA.vm_start);

                protection = thisVMA.vm_flags;
                printk("$$$$ Permission of the VMA $$$$\n");
                printk("Read --> %s \n", protection&PROT_READ?"yes":"no");
                printk("Write --> %s \n", protection&PROT_WRITE?"yes":"no");
                printk("Execute --> %s \n", protection&PROT_EXEC?"yes":"no");

                if (thisVMA.vm_file != NULL)
                {
                        fileName = d_path(&thisVMA.vm_file->f_path, (char*)__get_free_page(GFP_TEMPORARY), PAGE_SIZE);
                        printk("-> Mapped file: %s\n", fileName);
                }
                totalSize += thisVMA.vm_end - thisVMA.vm_start;
            
                if (count != numVMAS-1)
                {
                    thisVMA = *(thisVMA.vm_next);
                }
        }
        printk("\n\nThe total VMA space size of all VMAs is %i\n", totalSize);

        return 1;
}

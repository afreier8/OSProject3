#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_vma_stats 341

int main(int argc, char *argv[])
{
        int processID;
    
        // requesst process id to test
        printf("Enter a process id to test: \n");
        scanf("%d", &processID);
        syscall(__NR_vma_stats, processID);
        return 0;
}

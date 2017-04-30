#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_vmaProperty 342

int main(int argc, char argv[])
{
        int processID;
        unsigned long address;

        // ask for user info
        printf("Process id to test:\n");
        scanf("%d", &processID);

        printf("Memory address to test:\n");
        scanf("%ld", &address);

        syscall(__NR_vmaProperty, address, processID);
        return 0;
}

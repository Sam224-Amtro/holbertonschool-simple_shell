#include <unistd.h>
#include <stdio.h>

int main(void)
{
    printf("PID  : %u\n", getpid());
    printf("PPID : %u\n", getppid());
    return 0;
}
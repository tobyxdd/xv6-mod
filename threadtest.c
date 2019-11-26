#include "user.h"

void test(void *arg)
{
    sleep(*(int *)arg);
    printf(1, "Damn, my pid=%d\n", getpid());
}

int main(int argc, char *argv[])
{
    int i;
    for (i = 1; i < 10; i++)
    {
        int local_i = i;
        thread_create(test, &local_i);
    }
}
#include "types.h"
#include "user.h"

int roundnum, rounds = 1;
int playernum;
int token = 0;
lock_t *lk;

void player(void *args)
{
    int tid = *(int *)args;
    if (roundnum < rounds)
        exit();
    while (roundnum >= rounds)
    {
        lock_acquire(lk);
        if (token == tid)
        {
            token++;
            if (token >= playernum)
                token %= playernum;
            printf(1, "Pass number no: %d, Thread %d is passing the token to thread %d\n", rounds, tid, token);
            rounds++;
        }
        lock_release(lk);
        sleep(5);
    }
    exit();
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf(1, "Invalid args\n");
        exit();
    }
    playernum = (int)(argv[1][0] - '0');
    roundnum = (int)(argv[2][0] - '0');

    lk = malloc(sizeof(lock_t));
    lock_release(lk);

    for (int i = 0; i < playernum; ++i)
    {
        thread_create(player, (void *)&i);
        sleep(10);
    }

    sleep(20 * roundnum);
    while (wait() >= 0)
        ;
    printf(1, "Simulation of Frisbee game has finished, %d rounds were played in total!", roundnum);
    exit();
}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int preP[2]) {
    close(preP[1]);
    int prime;
    if(read(preP[0], &prime, sizeof(int)) != sizeof(int))
    {
        close(preP[0]);
        exit(0);
    }

    fprintf(1, "prime %d\n", prime);
    int p[2];
    pipe(p);
    int pid = fork();

    if(pid == 0) 
    {
        primes(p);
    }
    else 
    {
        //parent
        close(p[0]);
        int n;
        while(read(preP[0], &n, sizeof(int)))
        {
            if(n % prime != 0)
            {
                write(p[1], &n, sizeof(int));
            }
        }
        close(p[1]);
        close(preP[0]);
        wait(0);
    }
}

int main() {
    int p[2];
    pipe(p);
    int pid = fork();
    if(pid == 0) 
    {
        primes(p);
    }
    else 
    {
        //parent
        close(p[0]);
        for(int i = 2; i <= 35; i += 1)
        {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}
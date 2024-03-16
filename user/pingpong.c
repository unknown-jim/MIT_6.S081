#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int p2c[2];
    int c2p[2];
    pipe(p2c);
    pipe(c2p);
    
    int pid = fork();

    if(pid == 0) {
        //child
        close(p2c[1]);
        close(c2p[0]);

        char c[1];
        read(p2c[0], &c, 1);
        fprintf(1, "%d: received ping\n", getpid());
        write(c2p[1], &c, 1);

        close(p2c[0]);
        close(c2p[1]);
    }
    else {
        //parent;
        close(p2c[0]);
        close(c2p[1]);
        
        char c[1] = {'a'};
        write(p2c[1], &c, 1);
        read(c2p[0], &c, 1);
        fprintf(1, "%d: received pong\n", getpid());

        close(p2c[1]);
        close(c2p[0]);
    }

    exit(0);
}
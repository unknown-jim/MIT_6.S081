#include "kernel/types.h"
#include "user.h"

int main(const int argc, const char** argv)
{
    if(argc != 2) {
        fprintf(2, "sleep\n");
        exit(-1);
    }

    sleep(atoi(argv[1]));
    exit(0);
}

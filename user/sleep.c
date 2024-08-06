#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
    if(argc==1)
    {
        printf("error sleep\n");
        exit(-1);
    }
    int i=atoi(argv[1]);
    sleep(i);
    exit(0);
}
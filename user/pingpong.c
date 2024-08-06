#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    char str[5];
    if(fork()==0)
    {
        read(p[0],str,5);
        close(p[0]);
        write(p[1],"pong",5);
        close(p[1]);
        printf("%d: received %s\n",getpid(),str);
        exit(0);
    }
    else
    {
        write(p[1],"ping",5);
        close(p[1]);
        read(p[0],str,5);
        close(p[0]);
        sleep(1);
        printf("%d: received %s\n",getpid(),str);
    }
    exit(0);
}

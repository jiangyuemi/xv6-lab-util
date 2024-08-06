#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void Fork(int oldm,int oldn,int m,int n,int k,int f)
{
    if(fork()==0){
        close(n);
        int c;
        int p[2];
        pipe(p);
        if(read(m,&c,1))
        {
            printf("prime %d\n",c);
            Fork(m,n,p[0],p[1],c,f+1);
        }
        exit(0);
    }
    else{
        if(!f)//沃德发,一个父子进程的写时复制，值40分钟    父子进程的写时复制，谁修改值谁指向那个新值，父子进程拥有相同的内容，可以根据if else选择执行
        {
            close(m);
            for(int i=2;i<=35;i++)
            {
                write(n,&i,1);
            }
            close(n);
        }
        else{
            int c;
            close(m);
            while(read(oldm,&c,1))
            {
                if(c%k)
                {
                    write(n,&c,1);
                }
            }
            close(oldm);
            close(n);
        }
        wait((int *)0);
    }
}
int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    Fork(0,0,p[0],p[1],0,0);
    exit(0);
}
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


char buf[512];
int main(int argc, char *argv[])
{
    if(argc<2){
        printf("error operator!!\n");
        exit(0);
    }
    int k=1;
    for(int i=0;i<argc;i++)
    {
        if(!strcmp(argv[i],(char *)"-n"))
        {
            k=2+i;
            break;
        }
    }
    read(0,buf,sizeof(buf));
    char *p[20];
    for(int i=0;i<argc;i++)p[i]=argv[i];
    for(int i=0;buf[i];i++)
    {
        int j=i;
        while(buf[i]!='\n')i++;
        memset(&p[argc],0,20-argc);
        int m;
        for(m=argc;j<i;j++)
        {
            p[m]=&buf[j];
            while(buf[j]!=' '&&j<i)j++;
            if(buf[j]==' ')
            {
                buf[j]=0; 
                m++;
            }
        }
        buf[i]=0;
        if(fork()==0){
                exec(p[k],&p[k]);//exec 执行对应文件的程序有对应的返回
            }
        else{
            wait((int *)0);
        }
    }
    exit(0);
}

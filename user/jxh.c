#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main()
{
    char *p[20]={0};
    char buf[512]={0};
    read(0,buf,sizeof(buf));
    p[0]="grep";
    p[1]="a";
    int m=2;
    for(int j=0;buf[j];j++)
    {
        p[m]=&buf[j];
        while(buf[j]!=' '&&buf[j]!='\n')j++;
        if(buf[j]==' ')
        {
            buf[j]=0; 
            m++;
        }
    }
    buf[sizeof(buf)]=0;
    for(int i=0;i<m;i++)printf("%d:%s\n",i,p[i]);
    // if(fork()==0){
    //     exec(p[0],p);
    // }else{
    //     wait((int *)0);
    // }
    exit(0);
}
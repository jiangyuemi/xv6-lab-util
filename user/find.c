#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
struct dirent de;
char *goal;
struct stat st;
int flag;
char *title=".";
char *subtitle="..";
void find(char *path)
{
    int fd;
    if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }
    char buf[512]={0};
    char *p=buf;
    memmove(p,path,strlen(path));
    p=buf+strlen(buf);
    *p++='/';
    while(read(fd,&de,sizeof(de))==sizeof(de))
    {
        if(!(memcmp(de.name,title,1)&&memcmp(de.name,subtitle,2)))
        {
            continue;
        }
        if(de.inum == 0)continue;
        memmove(p,de.name,DIRSIZ);//沃德发一个DIRSIZ值40分钟
        stat(buf, &st);
        if(st.type==T_DIR)
        {
            if(flag)
            {
                find(buf);
            }
        }
        else if(st.type==T_FILE)
        {
            if(!memcmp(de.name,goal,strlen(goal)))
            {
                write(1,buf,sizeof(buf));//printf()和write(1)的区别是啥
                write(1, "\n", 1);
            }
        }

    }
    close(fd);
}
int main(int argc, char *argv[])
{
    if(argc<2)
    {
        printf("operation error !!\n");
        exit(0);
    }
    if(!memcmp(argv[1],title,1))
    {
        flag=1;
        goal=argv[2];
    }
    else goal=argv[1];
    find(".");
    
    exit(0);
}

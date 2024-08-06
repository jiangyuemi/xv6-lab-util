#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i;
  for(i = 1; i < argc; i++)
  {
    for(int j=0;argv[i][j];j++)
    {
      char c;
      if(argv[i][j]=='"')continue;
      else if(argv[i][j]=='\\'){  //对转义字符进行了处理,区别若是字符指针它解析为对应的字符串，例如'\n'的话，char*解析为'\'和'n'
        switch(argv[i][++j]){
          case 'n':
          c='\n';
          write(1,&c,1);
          break;
          case 'r':
          c='\r';
          write(1,&c,1);
          break;
        }
        continue;
      }
      write(1,&argv[i][j],1);
    }
    if(i + 1 < argc){
      write(1, " ", 1);
    } else {
      write(1, "\n", 1);
    }
  }
  exit(0);
}

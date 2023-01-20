touch

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        printf(1,"Usage: touch [files]...\n");
        exit();
    }
    int i,err;
    for(i=1;i<argc;i++)
    {
        if((err=open(argv[i],O_CREATE|O_RDWR)) < 0)
        {
            printf(1,"touch: error where creating %s\n",argv[i]);
            exit();
        }
        close(err);
    }
    exit();
}

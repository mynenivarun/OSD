#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc,char *argv[])
{
    if(argc<2)
    {
        exit();
    }
    if(chdir(argv[1])!= 0)
    {
        exit();
    }
    exit();
}

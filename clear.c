#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void help(){
    printf(1,"clear : Membersihkan layar terminal\n");
    printf(1,"clear [OPTION]\n");
    printf(1,"Option:\n");
    printf(1,"--help : Memperlihatkan bantuan lalu exit\n");
    printf(1,"--versi : Menunjukan informasi tentang versi lalu exit\n");
}

void prog(){
printf(1,"clear version 1.00\n");
printf(1,"Dibuat oleh Ferdinand Jason, Nurlita Dhuha, Alvin Tanuwijaya, Bagus Aji Sinto\n");
}

int main(int argc,char *argv[])
{
    if(argv[1][0]=='-'){
	if(strcmp(argv[1],"--help")==0) help();
	else if(strcmp(argv[1],"--versi")==0) prog();
	else printf(1,"pwd: invalid opsi %s\nCoba ketik 'clear --help' untuk informasi lebih lanjut\n",argv[1]);
	exit();
    }
    else printf(1,"\033[2J\033[1;1H\n");
    exit();
}

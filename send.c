#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>

#define port 0x337
//#define port 0x0337

int main(int argc, char **argv){
    if (argc < 2){
        printf("./send value \n\t value  --  [0 ~ 255]\n");
        return 1;
    }
    if (ioperm(port, 3, 1)){
        printf("I/O perms error\n");
        return 1;
    }
    int value = atoi(argv[1]);
    outb(value, port);
    printf("Send %d at port %d\n", value, port);
    return 0;
}


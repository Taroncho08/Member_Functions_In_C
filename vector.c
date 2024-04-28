#include <stdio.h>
#include "vector.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <ctype.h>
#include <math.h>


struct vector myvec;

int toDecimal(char *num)
{
    int len = 1;
    int dec = 0;
    int val = 0;

    for (int i = 0; i < 2; ++i)
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            val = num[i] - '0';
        }

        if (num[i] >= 'a' && num[i] <= 'f')
        {
            val = num[i] - 97 + 10;
        }

        dec += val * pow(16, len);
        --len;
    }
    return dec;
}

void cton(struct vector *vec)
{
    struct stat st;
    char arr[100] = "gcc -c set.c -DADDRESS=";
    char *objdump = "objcopy -O binary -j .text set.o text.txt";
    // char *redirect = "od -An -v -t x1 text.txt > file.txt";
    unsigned long long addr = (unsigned long long)vec;

    sprintf(arr + strlen(arr), "%lld", addr);

    system(arr);
    system(objdump);

    int fd;

    if ((fd = open("text.txt", O_RDWR)) < 0)
    {
        perror("file");
        exit(1);
    }  

    if (fstat(fd, &st) < 0)
    {
        perror("fstat");
        exit(1);
    }

    if (!S_ISREG (st.st_mode)) {
        perror ("file");
        exit(1);
    }

    int size = 0;
    size = st.st_size;

    unsigned char *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED , fd, 0);


    if (close(fd) < 0)
    {
        perror("close");
        exit(1);
    }

    vec->set = ptr;
    vec->size = size;
    
}

void destroy(struct vector *vec)
{
    if (munmap(vec->set, vec->size) < 0)
    {
        perror("unmap");
        exit(1);
    }
}

int main()
{
    struct vector vec;
    cton(&vec);

    vec.set(4, 5);

    cton(&myvec);
    myvec.set(3, 1);

    printf("%d %d\n", myvec.x, myvec.y);

}
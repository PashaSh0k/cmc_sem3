#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int to_int(int file, int position){
    lseek(file, position, SEEK_SET);
    int number;
    read(file, &number, 4);
    return number;
}
void write_number(int file, int number){
    int digits = 1;
    int saved = number;
    while(saved){
        saved = saved / 10;
        digits = digits * 10;
    }
    char tmp;
    while(number){
        digits = digits / 10;
        tmp = (char)(number/digits) + '0';
        write(file, &tmp, 1);
        number = number % digits;
    }
    tmp = ' ';
    write(file, &tmp, 1);
}
int main(int argc, char** argv){
    int f1 = open(argv[1], O_RDWR, 0666);
    if(f1 == -1){
        printf("error");
        return 0;
    }
    struct stat f1_stat;
    stat(argv[1], &f1_stat);
    int f2 = open(argv[2], O_RDWR|O_TRUNC|O_CREAT, 0666);
    struct stat f2_stat;
    stat(argv[2], &f2_stat);
    if(f1_stat.st_ino == f2_stat.st_ino){
        printf("equal files");
        return 0;
    }
    int size = f1_stat.st_size;
    int tmp1, tmp2;
    int i, j;
    for(i = 0; i < size - 4; i += 4)
        for(j = i + 4; j < size; j+= 4)
            if(to_int(f1, i) >= to_int(f1, j)){
                // swap
                lseek(f1, i, SEEK_SET);
                read(f1, &tmp1, 4);
                lseek(f1, j, SEEK_SET);
                read(f1, &tmp2, 4);
                lseek(f1, i, SEEK_SET);
                write(f1, &tmp2, 4);
                lseek(f1, j, SEEK_SET);
                write(f1, &tmp1, 4);
            }
    lseek(f1, 0, SEEK_SET); 
    char sign;
    while(read(f1, &tmp1, 4) == 4){
        if(tmp1 < 0){
            sign = '-';
            write(f2, &sign, 1);
            write_number(f2, -1*tmp1);
        }
        else if(tmp1 == 0){
            sign = '0';
            write(f2, &sign, 1);
        }
        else
            write_number(f2, tmp1);
    }
    sign = '\n';
    write(f2, &sign, 1);
    close(f1);
    close(f2);
    return 0;   
}
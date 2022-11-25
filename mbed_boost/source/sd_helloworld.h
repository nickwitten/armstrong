#include "mbed.h"
#include "SDFileSystem.h"

SDFileSystem sd(p5, p6, p7, p8, "sd");
Serial pc(USBTX, USBRX);

int main() {
    FILE *fp = fopen("/sd/test.txt", "w");
    fprintf(fp, "Hello World!\n");
    fclose(fp);
    fp = fopen("/sd/test.txt", "r");
    size_t buff_size = 100;
    char buff[buff_size];
    fgets(buff, buff_size, fp);
    pc.printf("%s\r\n", buff);
}

#include "mbed.h"
#include "rtos.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
Thread thread2;

void led2_thread() {
    while (true) {
        led2 = !led2;
        Thread::wait(1000);
    }
}

void led3_thread(const void *wait_time_p) {
    int w_time = *(int*)wait_time_p;
    while (true) {
        led3 = !led3;
        Thread::wait(w_time);
    }
}

void led4_thread() {
    while (true) {
        led4 = !led4;
        Thread::wait(250);
    }
}
 
int main() {
    thread2.start(led2_thread);
    int time = 750;
    Thread thread3(led3_thread, &time);
    Thread thread4(led4_thread);
    while (true) {
        led1 = !led1;
        Thread::wait(500);
    }
}

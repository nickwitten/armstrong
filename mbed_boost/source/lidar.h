#include "mbed.h"
#include "VL53L0X.h"

Serial pc(USBTX,USBRX);
DigitalOut shdn(p26);
DevI2C _i2c(VL53L0_I2C_SDA, VL53L0_I2C_SCL);
VL53L0X lidar(_i2c, shdn, p25);

//I2C sensor pins
#define VL53L0_I2C_SDA   p28
#define VL53L0_I2C_SCL   p27


int main()
{
    int status;
    uint32_t distance;

    status = lidar.init_sensor(0x54); // 0x54 I2C Address
    if (status) {
        pc.printf("%i\r\n", status);
        pc.printf("Failed to init board! \r\n");
        return -1;
    }

    while (1) {
        status = lidar.get_distance(&distance);
        if (status == VL53L0X_ERROR_NONE) {
            pc.printf("D=%ld mm\r\n", distance);
        }
        if (status == VL53L0X_ERROR_RANGE_ERROR) {
            pc.printf("Out of Range");
        }
    }
}

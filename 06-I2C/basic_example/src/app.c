

#include "gd32vf103.h"
#include "delay.h"
#include "lcd.h"

/* The address of the device to read from. This example uses an MPU6500. To use another device change this to the appropriate address */
#define I2C_DEVICE_ADDR 0x69

/* The register to read from, for this example we are reading the "who am I" register of the MPU6500 if all is well this should read decimal 17 */
#define I2C_READ_REG    0x75


void i2c_read_register(int32_t port, uint8_t addr, uint8_t reg, uint8_t size, uint8_t *data);
void i2c_write_register(int32_t port, uint8_t addr, uint8_t reg, uint8_t size, uint8_t *data);

int main(void)
{
    /* This example implements the hardware I2C interface to communicate with outside I2C devices */

    /* Some LCD setup */
    uint8_t read_buffer[64] = {0};
    Lcd_SetType(LCD_INVERTED);
    Lcd_Init();
    LCD_Clear(BLACK);
    LCD_ShowString(0, 20, "I2C example", BLUE);
    LCD_Wait_On_Queue();

    /* Start the different clocks needed for the I2C bus */
    rcu_periph_clock_enable(RCU_I2C0);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_AF);

    /* Initialize the GPIO connected to the I2C0 bus */
    gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);
    
    /* Configure i2c clock speed and dutycycle */
    i2c_clock_config(I2C0, 400000, I2C_DTCY_2);

    /* Enable i2c */
    i2c_enable(I2C0);

    /* Read a register on the i2c bus */
    i2c_read_register(I2C0, I2C_DEVICE_ADDR, I2C_READ_REG, 1, read_buffer);
    /* A write would look like this */
    // i2c_write_register(I2C0, I2C_DEVICE_ADDR, [register that you want to read], [bytes to read], [results stored in this buffer]);
    // Look below to see how this is implemented



    /* Show the received data */
    LCD_ShowStr(0,0,"Read: ", GREEN, TRANSPARENT);
    LCD_ShowNum(8*6, 0, read_buffer[0], 3, YELLOW);
    LCD_Wait_On_Queue();
    while(1);

}

/* You can copy this function to be able to read from most i2c devices */
void i2c_read_register(int32_t port, uint8_t addr, uint8_t reg, uint8_t size, uint8_t *data){

    /* send a start condition to I2C bus */
    i2c_start_on_bus(port);
    while(!i2c_flag_get(port, I2C_FLAG_SBSEND));

    /* send slave address to I2C bus with write flag */
    i2c_master_addressing(port, addr << 1, I2C_TRANSMITTER);
    /* Wait for sending address to finish */
    while(!i2c_flag_get(port, I2C_FLAG_ADDSEND));
    i2c_flag_clear(port, I2C_FLAG_ADDSEND);

    /* Send which register to read */
    i2c_data_transmit(port, reg);
    /* wait until the data has been sent */
    while(!i2c_flag_get(port, I2C_FLAG_TBE));

    /* Send new start condition */
    i2c_start_on_bus(port);
    while( ! i2c_flag_get(port, I2C_FLAG_SBSEND) );

    /* Now send address with read flag */
    i2c_master_addressing(port, addr << 1, I2C_RECEIVER);
    while( ! i2c_flag_get(port, I2C_FLAG_ADDSEND) );
    i2c_flag_clear(port, I2C_FLAG_ADDSEND);

    /* Enable acknowledge for receiving multiple bytes */
    i2c_ack_config(port, I2C_ACK_ENABLE);

    /* Receive bytes, read into buffer. */
    for(int i = 0; i < size; i++) {
        if(i == size - 1) {
            /* If last byte, do not send ack */
            i2c_ack_config(port, I2C_ACK_DISABLE);
        }
        while(!i2c_flag_get(port, I2C_FLAG_RBNE));
        *data++ = i2c_data_receive(port);
    }

    i2c_stop_on_bus(port);
    while( I2C_CTL0(port) & I2C_CTL0_STOP );
}

/* You can copy this function to be able to write most i2c devices */
void i2c_write_register(int32_t port, uint8_t addr, uint8_t reg, uint8_t size, uint8_t *data)
{    
    /* send a NACK for the next data byte which will be received into the shift register */
    while(i2c_flag_get(port, I2C_FLAG_I2CBSY));

    /* send a start condition to I2C bus */
    i2c_start_on_bus(port);
    while(!i2c_flag_get(port, I2C_FLAG_SBSEND));

    /* send slave address to I2C bus */
    i2c_master_addressing(port, addr << 1, I2C_TRANSMITTER);
    while(!i2c_flag_get(port, I2C_FLAG_ADDSEND));
    i2c_flag_clear(port, I2C_FLAG_ADDSEND);

    
    /* Send which register to write */
    i2c_data_transmit(port, reg);
    /* wait until the TBE bit is set */
    while(!i2c_flag_get(port, I2C_FLAG_TBE));

    /* Send data */
    for(int i = 0; i < size; i++){
        i2c_data_transmit(port, *data++);
        /* wait until the TBE bit is set */
        while(!i2c_flag_get(port, I2C_FLAG_TBE));
    }

    /* Send stop condition */
    i2c_stop_on_bus(port);
    while( I2C_CTL0(port) & I2C_CTL0_STOP );
}



#ifndef _MANGA_SCREEN_I2C_H_
#define _MANGA_SCREEN_I2C_H_


#include "MangaScreen.h"
#include <stdlib.h>
#include <stdio.h>


typedef uint16_t u16;
typedef unsigned long int u32;
typedef uint8_t  u8;


struct i2c_msg {
        u16 addr;     /* slave address                        */
        u16 flags;
#define I2C_M_TEN               0x0010  /* this is a ten bit chip address */
#define I2C_M_RD                0x0001  /* read data, from slave to master */
#define I2C_M_STOP              0x8000  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NOSTART           0x4000  /* if I2C_FUNC_NOSTART */
#define I2C_M_REV_DIR_ADDR      0x2000  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK        0x1000  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NO_RD_ACK         0x0800  /* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_RECV_LEN          0x0400  /* length will be first received byte */
        u16 len;              /* msg length                           */
        u8 *buf;              /* pointer to msg data                  */
};

int i2c_transfer(struct i2c_msg *msgs, int num);
int i2c_send2(uint16_t addr, const u8 *buf, int count);
int i2c_recv2(uint16_t addr, u8 *buf, int count);
int i2c_recv(uint16_t addr, u8 *buf, int count);
int i2c_send(uint16_t addr, const u8 *buf, int count);
void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(uint8_t u8data);
uint8_t TWI_Read(char ack);
uint8_t TWI_GetStatus(void);
#endif

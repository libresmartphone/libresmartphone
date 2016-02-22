

#include "i2c.h"

/**
 * i2c_transfer - execute a single or combined I2C message
 * @msgs: One or more messages to execute before STOP is issued to
 *	terminate the operation; each message begins with a START.
 * @num: Number of messages to be executed.
 *
 * Returns negative errno, else the number of messages executed.
 *
 * Note that there is no requirement that each message be sent to
 * the same slave address, although that is the most common model.
 */

#define I2C_ADDR 0x38

int i2c_transfer(struct i2c_msg *msgs, int num){
	int ret, i;


/*#ifdef DEBUG
	for (ret = 0; ret < num; ret++) {
		dev_dbg("master_xfer[%d] %c, addr=0x%02x, "
			"len=%d%s\n", ret, (msgs[ret].flags & I2C_M_RD)
			? 'R' : 'W', msgs[ret].addr, msgs[ret].len,
			(msgs[ret].flags & I2C_M_RECV_LEN) ? "+" : "");
	}
#endif*/
	
    for(i=0; i<num; i++){
        if(msgs[i].flags & I2C_M_RD){
            ret = i2c_recv2(msgs[i].addr, msgs[i].buf, msgs[i].len);
            if(ret){
                dev_err("i2c_recv2 err: 0x%x\n", ret);
                return ret;
            }
        }        
        else{
            ret = i2c_send2(msgs[i].addr, msgs[i].buf, msgs[i].len);
            if(ret){
                dev_err("i2c_send2 err: 0x%x\n", ret);
                return ret;
            }
        }
    }
	return num;
}


// Send a message via I2C
int i2c_send2(uint16_t addr, const u8 *buf, int count){
	int i;
	int stat;

	TWI_Start();						// First start condition 
	stat = TWI_GetStatus();
    if (stat != 0x08){ //0x08
        dev_err("Status err wr 1 %d\n", stat);
        return stat;
    }

	TWI_Write((addr<<1));		// Chip address + write
	stat = TWI_GetStatus();
    if (stat != 0x18){
        dev_err("Status err wr 2 %d\n", stat);
        return stat;
    }

	for(i=0; i<count; i++){				// write the data
		TWI_Write(buf[i]);
		stat = TWI_GetStatus();
		if (stat != 0x28){
            dev_err("Status err wr 3 %d\n", stat);
		    return stat;
        }
	}
	TWI_Stop();							// Send stop condition 

	return 0;
}


// Receive count bytes from addr
int i2c_recv2(uint16_t addr, u8 *buf, int count){
	int i;
	int stat;

	TWI_Start();						// First start condition 
	stat = TWI_GetStatus();
    if (stat != 0x08){
        dev_err("Status err rd 1: 0x%x\n", stat);
        return stat;
    }

	TWI_Write((addr<<1)|0x01);		// Chip address + READ
	stat = TWI_GetStatus();
    if (stat != 0x40){
        dev_err("Status err rd 2: 0x%x\n", stat);
        return stat;
    }

	for(i=0; i<count-1; i++){			
		buf[i] = TWI_Read(1);			// Read the data and ACK
	}
	buf[count-1] = TWI_Read(0);			// No ack on last byte
	TWI_Stop();							// Send stop condition 
	
	return 0;
}



/**************************************
 * A bit higher level stuff 
 **************************************/

// Receive count bytes from addr
int i2c_recv(uint16_t addr, u8 *buf, int count){
	int i;
	int stat;

	TWI_Start();						// First start condition 
	stat = TWI_GetStatus();
    if (stat != 0x08){
        dev_err("Status err 1\n");
        return stat;
    }

	TWI_Write((I2C_ADDR<<1));		// Chip address + write
	stat = TWI_GetStatus();
    if (stat != 0x18){
        dev_err("Status err 2\n");
        return stat;
    }

	TWI_Write((addr & 0x00FF));			// Address low byte
	stat = TWI_GetStatus();
    if (stat != 0x28){
        dev_err("Status err 3\n");
        return stat;
    }

	TWI_Write((addr<<8 & 0xFF00));		// Address high byte
	stat = TWI_GetStatus();
    if (stat != 0x28){
        dev_err("Status err 4\n");
        return stat;
    }

	TWI_Start();						// Second start condition 	
	stat = TWI_GetStatus();
    if (stat != 0x10){
        dev_err("Status err 5\n");
        return stat;
    }

	TWI_Write((I2C_ADDR<<1) | 0x01);	// Chip address + read
	stat = TWI_GetStatus();
    if (stat != 0x40){
        dev_err("Status err\n");
        return stat;
    }

	for(i=0; i<count-1; i++){			
		buf[i] = TWI_Read(1);			// Read the data and ACK
	}
	buf[count-1] = TWI_Read(0);			// No ack on last byte
	TWI_Stop();							// Send stop condition 
	
	return 0;
}


// Send a message via I2C
int i2c_send(uint16_t addr, const u8 *buf, int count){
	int i;
	int stat;

	TWI_Start();						// First start condition 
	stat = TWI_GetStatus();
    if (stat != 0x08){
        dev_err("Status err wr 1\n");
        return stat;
    }

	TWI_Write((I2C_ADDR<<1));		// Chip address + write
	stat = TWI_GetStatus();
    if (stat != 0x18){
        dev_err("Status err wr 2\n");
        return stat;
    }

	TWI_Write((addr & 0x00FF));			// Address low byte
	stat = TWI_GetStatus();
    if (stat != 0x28){
        dev_err("Status err wr 3\n");
        return stat;
    }

	TWI_Write((addr<<8 & 0xFF00));		// Address high byte
	stat = TWI_GetStatus();
    if (stat != 0x28){
        dev_err("Status err wr 4\n");
        return stat;
    }

	for(i=0; i<count; i++){				// write the data
		TWI_Write(buf[i]);
		stat = TWI_GetStatus();
		if (stat != 0x28)
		    return stat;
	}
	TWI_Stop();							// Send stop condition 

	return 0;
}
/**************************************
 * Low level I2C stuff
 **************************************/

void TWI_Init(void){
    //set SCL to 400kHz
    TWSR = 0x00;
    TWBR = 0x0C;
    //enable TWI
    TWCR = (1<<TWEN);
}

// Send start signal 
void TWI_Start(void){
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

//send stop signal
void TWI_Stop(void){
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

// Write a byte
void TWI_Write(uint8_t u8data){
    TWDR = u8data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

//read byte with NACK
uint8_t TWI_Read(char ack){
    TWCR = (1<<TWINT)|(1<<TWEN)|((ack?1:0)<<TWEA);
    while ((TWCR & (1<<TWINT)) == 0);
    return TWDR;
}

// Get TWI status
uint8_t TWI_GetStatus(void){
    return TWSR & 0xF8;
}



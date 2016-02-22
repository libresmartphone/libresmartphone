/** Digitizer - Communication and control with either 
FocalTech FT6X06 capacitive touch screen controller */
/*
	Most of the code in this file was taken from the Linux kernel, 
	here is the lisence that was included. 
	Copyright (C) 2014 Intelligent Agent AS
	Autor: Elias Bakken elias.bakken@gmail.com

*/
/*
 * Copyright (C) 2012 Simon Budig, <simon.budig@kernelconcepts.de>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * This is a driver for the EDT "Polytouch" family of touch controllers
 * based on the FocalTech FT5x06 line of chips.
 *
 * Development of this driver has been sponsored by Glyn:
 *    http://www.glyn.com/Products/Displays
 *
 *
*/


#include "Digitizer.h"

#define CONFIG_DIGITIZER_NORMAL 0
#define CONFIG_DIGITIZER_NORMAL_INV_X 1
#define CONFIG_DIGITIZER_NORMAL_INV_Y 2
#define CONFIG_DIGITIZER_NORMAL_INV_XY 3
#define CONFIG_DIGITIZER_SWITCH 4
#define CONFIG_DIGITIZER_SWITCH_INV_X 5
#define CONFIG_DIGITIZER_SWITCH_INV_Y 6

struct edt_ft5x06_ts_data *tsdata;
struct touch_point tp[2];
static int num_touches;
static int num_touches_prev;
static int report_nr;

static int digitizer_config_xy = CONFIG_DIGITIZER_NORMAL_INV_XY;

ISR(INT2_vect){
    edt_ft5x06_get_data();
} 

int setup_irq(void){
    EICRA |= (1 << ISC21); // Falling edge
    EIMSK |= (1 << INT2);  // Enable INT2
    sei(); 
    return 0;
}

int edt_ft5x06_ts_identify(struct edt_ft5x06_ts_data *tsdata){
    int lib_ver = 0;
    int fw_id;
    
    int reg;
    reg = edt_ft5x06_register_read(tsdata, REG_CIPHER);

    if(reg != 0x06){
        return -1;
    }
    reg = edt_ft5x06_register_read(tsdata, REG_FOCALTECH_ID);
    if (reg != 0x11 && reg != 144){
        dev_err("Wrong focaltech ID: %d\n", reg);
        return -2;
    }
    lib_ver |= (edt_ft5x06_register_read(tsdata, REG_LIB_VER_H)<<8);
    lib_ver |= (edt_ft5x06_register_read(tsdata, REG_LIB_VER_L)<<0);

    strcpy(tsdata->name, "FT6206");
    fw_id = edt_ft5x06_register_read(tsdata, REG_FIRMID);
    sprintf(tsdata->fw_version, "%d:%d", fw_id, lib_ver);
    
    if( edt_ft5x06_register_read(tsdata, 0x00) == 0x00)
        dev_dbg("Chip is in working mode\n");
    else
        dev_dbg("Chip is in factory mode\n");

	return 0;
}

struct edt_ft5x06_attribute {
	size_t field_offset;
	u8 limit_low;
	u8 limit_high;
	u8 addr;
};

#define EDT_ATTR(_field, _mode, _addr, _limit_low, _limit_high)		\
	struct edt_ft5x06_attribute edt_ft5x06_attr_##_field = {	\
		.field_offset = offsetof(struct edt_ft5x06_ts_data, _field),	\
		.limit_low = _limit_low,				\
		.limit_high = _limit_high,				\
		.addr = _addr,						\
	}


static EDT_ATTR(threshold,           0, REG_TH_GROUP, 0, 255);
static EDT_ATTR(filter_coeff,        0, REG_TH_DIFF, 0, 255);
static EDT_ATTR(time_enter_monitor,  0, REG_TIMEENTERMONITOR, 0, 255);
static EDT_ATTR(report_rate_active,  0, REG_PERIODACTIVE, 3, 14);
static EDT_ATTR(report_rate_monitor, 0, REG_PERIODMONITOR, 3, 14);

#define EDT_ATTR_CHECKSET(name, reg) \
	if (tsdata->name >= edt_ft5x06_attr_##name.limit_low &&		\
	    tsdata->name <= edt_ft5x06_attr_##name.limit_high)		\
		edt_ft5x06_register_write(tsdata, reg, tsdata->name)


void
edt_ft5x06_ts_set_parameters(struct edt_ft5x06_ts_data *tsdata){
	EDT_ATTR_CHECKSET(threshold,           REG_TH_GROUP);
	EDT_ATTR_CHECKSET(filter_coeff,        REG_TH_DIFF);
	EDT_ATTR_CHECKSET(time_enter_monitor,  REG_TIMEENTERMONITOR);
	EDT_ATTR_CHECKSET(report_rate_active,  REG_PERIODACTIVE);
	EDT_ATTR_CHECKSET(report_rate_monitor, REG_PERIODMONITOR);
}

void
edt_ft5x06_ts_get_parameters(struct edt_ft5x06_ts_data *tsdata){
	tsdata->threshold           = edt_ft5x06_register_read(tsdata, REG_TH_GROUP);
    tsdata->filter_coeff        = edt_ft5x06_register_read(tsdata, REG_TH_DIFF);
	tsdata->time_enter_monitor  = edt_ft5x06_register_read(tsdata, REG_TIMEENTERMONITOR);
    tsdata->report_rate_active  = edt_ft5x06_register_read(tsdata, REG_PERIODACTIVE);
    tsdata->report_rate_monitor = edt_ft5x06_register_read(tsdata, REG_PERIODMONITOR);
}

void edt_ft5x06_print_parameters(struct edt_ft5x06_ts_data *tsdata){
    dev_dbg("Threshold: %d\n", tsdata->threshold);
    dev_dbg("Filter_coeff: %d\n", tsdata->filter_coeff );
    dev_dbg("Time_enter_monitor: %d\n", tsdata->time_enter_monitor);
    dev_dbg("Report rate active: %d\n", tsdata->report_rate_active);
    dev_dbg("Report rate monitor: %d\n", tsdata->report_rate_monitor);
}

int digitizer_init(void){
	const struct edt_ft5x06_platform_data *pdata;
	
	int error;

	dev_dbg("probing for EDT FT6x06 I2C\n");

	tsdata = malloc(sizeof(struct edt_ft5x06_ts_data));
	if (!tsdata) {
		dev_err("Failed to allocate memory\n");
		return -ENOMEM;
	}

	pdata = malloc(sizeof(struct edt_ft5x06_platform_data));
	if (!pdata) {
		dev_err("Failed to allocate memory for pdata\n");
		return -ENOMEM;
	}

    // Pins for Digitizer
	DDRB |= PIN_S4;	// PB6 (Reset)
    PORTB &= ~PIN_S4;
	_delay_ms(2);
    PORTB |= PIN_S4;
	_delay_ms(100);

    // INT in input mode
	DDRD &= ~PIN_S3;	// PD2 (Int)
	TWI_Init();
    
    tsdata = malloc(sizeof(struct edt_ft5x06_ts_data));
	if (!tsdata) {
		dev_err("failed to allocate driver data.\n");
		error = -ENOMEM;
		return error;
	}
    
	tsdata->factory_mode = false;

	error = edt_ft5x06_ts_identify(tsdata);
	if (error) {
		dev_err("touchscreen probe failed, errno: %d\n", error);
		return error;
	}

	edt_ft5x06_ts_get_parameters(tsdata);
    edt_ft5x06_print_parameters(tsdata);
    tsdata->threshold = 30  ;
	edt_ft5x06_ts_set_parameters(tsdata);
   

    //edt_ft5x06_register_write(tsdata, 0x80, 128);
    //edt_ft5x06_register_write(tsdata, 0x88, 60);

	dev_dbg("Model \"%s\", Rev. \"%s\", Report rate: %d\n",
		tsdata->name, tsdata->fw_version, tsdata->report_rate_active);

    report_nr = 0;
    setup_irq();

	dev_dbg("EDT FT6x06 initialized");

	return 0;
}

/* Set the digitizer configuration */
int digitizer_set_config(int config){
    if(config > 0 && config < 6){
        digitizer_config_xy = config;
        return 0;
    }
    return -1;
}

/* This is initiliazed from the host. Return the current touch point data */
int digitizer_get_report(USB_DigitizerReport_Data_t* report){	
    int ret;

    if(tp[report_nr].reported == 0){
        //dev_dbg("Down %d, id: %d\n", report_nr, tp[report_nr].id);
        report->Tip_and_InRange       = (tp[report_nr].event & TOUCH_EVENT_ON) ? 1 : 0;
        report->Pressure              = 1; // tp[report_nr].weight;
        report->Contact_identifier    = tp[report_nr].id;
        report->Contact_count_max     = MAX_SUPPORT_POINTS;	
        switch(digitizer_config_xy){
            case CONFIG_DIGITIZER_NORMAL:
                report->X = tp[report_nr].x;
                report->Y = tp[report_nr].y;
                break;
            case CONFIG_DIGITIZER_NORMAL_INV_X:
                report->X = 480-tp[report_nr].x;
                report->Y = tp[report_nr].y;
                break;
            case CONFIG_DIGITIZER_NORMAL_INV_Y:
                report->X = tp[report_nr].x;
                report->Y = 800-tp[report_nr].y;
                break;
            case CONFIG_DIGITIZER_NORMAL_INV_XY:
                report->X = 480-tp[report_nr].x;
                report->Y = 800-tp[report_nr].y;
                break;                
            case CONFIG_DIGITIZER_SWITCH:
                report->X = tp[report_nr].y;
                report->Y = tp[report_nr].x;
                break;
            case CONFIG_DIGITIZER_SWITCH_INV_X:
                report->X = 800-tp[report_nr].y;
                report->Y = tp[report_nr].x;
                break;
            case CONFIG_DIGITIZER_SWITCH_INV_Y:
                report->X = tp[report_nr].y;
                report->Y = 480-tp[report_nr].x;
                break;
        }
        tp[report_nr].reported = 1;
        tp[report_nr].notseen = 0;
        ret = 0;
    }
    else if(tp[report_nr].notseen == 10){        
        //dev_dbg("Lift %d, %d, id: %d\n", report_nr, tp[report_nr].notseen, tp[report_nr].id);
        report->Tip_and_InRange       = 0;
        report->Pressure              = 0;
        report->Contact_identifier    = tp[report_nr].id;
        report->Contact_count_max     = MAX_SUPPORT_POINTS;	
        report->X = 0;
        report->Y = 0;
        tp[report_nr].notseen++;
        ret = 0;        
    }
    else{
        tp[report_nr].notseen++;
        if(tp[report_nr].notseen > 12)
            tp[report_nr].notseen = 12;
        ret = -1;
    }

    report_nr++;
    report_nr %= MAX_SUPPORT_POINTS;

	return ret;
}

/* Fetch touch data and place it in the tp structs */
int edt_ft5x06_get_data(void){
    //int gest_id;
    u8 rdbuf[16];
    u8 wrbuf[1];
    int i;    
    int ret;
    
    wrbuf[0] = 0;
    ret = edt_ft5x06_ts_readwrite(1, wrbuf, 16, rdbuf);
    if(ret != 0)
        return ret;
    num_touches = rdbuf[2];
    //gest_id = rdbuf[1];
    dev_dbg("num_touch: %d\n", num_touches);
    // When no touch has occured, 255 is sent. 
    if(num_touches == 255){
        num_touches = 0;
        dev_dbg("Num touches = 255\n");
    }

    // A contact has been removed. 
    // 
    if(num_touches < num_touches_prev){

    }

    for(i=0; i<num_touches; i++){
        // Only update touch points that have been reported
        if(tp[i].reported == 1){
            tp[i].x      = ((rdbuf[REG_P1_XH     + i*6] & 0x0F) << 8) + rdbuf[REG_P1_XL+i*6];
            tp[i].y      = ((rdbuf[REG_P1_YH     + i*6] & 0x0F) << 8) + rdbuf[REG_P1_YL+i*6];
            tp[i].event  = ((rdbuf[REG_P1_XH     + i*6] & 0xC0) >> 6);            
            tp[i].id     = ((rdbuf[REG_P1_YH     + i*6] & 0xF0) >> 4);
            tp[i].area   = ((rdbuf[REG_P1_MISC   + i*6] & 0xF0) >> 4);
            tp[i].weight =   rdbuf[REG_P1_WEIGHT + i*6];
            tp[i].reported = 0;
            dev_dbg("%d: (x, y, a, w, e, i) =  (%d,%d, %d, %d, %d, %d)\n",
                i, tp[i].x, tp[i].y, tp[i].area, tp[i].weight, tp[i].event, tp[i].id);
        }
    }
    
    return 0;
}

int edt_ft5x06_register_write(struct edt_ft5x06_ts_data *tsdata, u8 addr, u8 value){
	u8 wrbuf[2];

    wrbuf[0] = addr;
    wrbuf[1] = value;

    return edt_ft5x06_ts_readwrite(2, wrbuf, 0, NULL);
}

int edt_ft5x06_register_read(struct edt_ft5x06_ts_data *tsdata, u8 addr){
	u8 wrbuf[1], rdbuf[1];
	int error;
    
    wrbuf[0] = addr;
	error = edt_ft5x06_ts_readwrite(1, wrbuf, 1, rdbuf);
	if (error)
		return error;
	return rdbuf[0];
}

int edt_ft5x06_ts_readwrite(
				   u16 wr_len, u8 *wr_buf,
				   u16 rd_len, u8 *rd_buf)
{
	struct i2c_msg wrmsg[2];
	int i = 0;
	int ret;

	if (wr_len) {
		wrmsg[i].addr  = CLIENT_ADDR;
		wrmsg[i].flags = 0;
		wrmsg[i].len = wr_len;
		wrmsg[i].buf = wr_buf;
		i++;
	}
	if (rd_len) {
		wrmsg[i].addr  = CLIENT_ADDR;
		wrmsg[i].flags = I2C_M_RD;
		wrmsg[i].len = rd_len;
		wrmsg[i].buf = rd_buf;
		i++;
	}

	ret = i2c_transfer(wrmsg, i);
	if (ret < 0)
		return ret;
	if (ret != i)
		return -EIO;

	return 0;
}


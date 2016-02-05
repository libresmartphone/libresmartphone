/** Digitizer - Communication and control with either 
Atmel mXT224 or Synaptics ClearPad 3000-series 
capacitive touch screen controller */

/*
	Most of the code in this file was taken from the Linux kernel, 
	here is the lisence that was included. 
	Copyright (C) 2013 Intelligent Agent AS
	Autor: Elias Bakken elias.bakken@gmail.com


 * Atmel maXTouch Touchscreen driver
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */


#include "Digitizer.h"

struct mxt_data *data;

/* Initialize the digitizer */
int Digitizer_Init(void){

	struct mxt_platform_data *pdata;
	int err; 

	DDRB &= ~PIN_S4;	// PB6
	DDRD &= ~PIN_S3;	// PD2

	data = malloc(sizeof(struct mxt_data));
	if (!data) {
		dev_err("Failed to allocate memory\n");
		return -ENOMEM;
	}

	pdata = malloc(sizeof(struct mxt_platform_data));
	if (!pdata) {
		dev_err("Failed to allocate memory for pdata\n");
		return -ENOMEM;
	}

	data->initialized = false;

	pdata->x_line			= 18;
	pdata->y_line			= 11;
	pdata->x_size			= 1024;
	pdata->y_size			= 600;
	pdata->blen				= 0x1;
	pdata->threshold		= 0x28;
	pdata->voltage			= 2800000;		/* 2.8V */
	pdata->orient			= MXT_DIAGONAL_COUNTER;
	pdata->irqflags			= IRQF_TRIGGER_FALLING;
	pdata->config 			= NULL;
	pdata->config_length	= 0;

	data->pdata = pdata;

	TWI_Init();
	dev_err("calling mxt_initialize\n");
	err = mxt_initialize(data);
	if (err) {
		dev_err("Unable to initilize TP\n");
		return -EIO;
	}

	/* Force the device to report back status so we can cache the device
	 * config checksum
	 */
	err = mxt_write_object(data, MXT_GEN_COMMAND_T6,
				 MXT_COMMAND_REPORTALL, 1);
	if (err){
		dev_warn("error making device report status.\n");
		return -EIO;	
	}

	data->initialized = true;

	return 0;
}


int Digitizer_get_report(USB_DigitizerReport_Data_t* DigitizerReport){	
	int ret;

	data->report = DigitizerReport;
	if(!data->initialized){
		dev_err("Digitizer is not initlialized = %x\n", ret);
		return -1;
	}

	ret = mxt_handle_messages(data, true);
	if (ret)
		dev_err("Failed to get Digitizer report. Err = %x\n", ret);

	return ret;
}



int mxt_read_num_messages(struct mxt_data *data, u8 *count){
	/* TODO: Optimization: read first message along with message count */
	return __mxt_read_reg(data->T44_address, 1, count);
}

int mxt_read_messages(struct mxt_data *data, u8 count, struct mxt_message *messages){
	return __mxt_read_reg(data->T5_address, sizeof(struct mxt_message) * count, messages);
}

unsigned mxt_extract_T6_csum(const u32 *csum){
	return csum[0] | (csum[1] << 8) | (csum[2] << 16);
}

bool mxt_is_T9_message(struct mxt_data *data, struct mxt_message *msg){
	u8 id = msg->reportid;
	return (id >= data->T9_reportid_min && id <= data->T9_reportid_max);
}

int mxt_proc_messages(struct mxt_data *data, u8 count, bool report){
	u8 reportid;
	struct mxt_message *messages, *msg;
	int ret;

	messages = malloc(count * sizeof(*messages));
	if (!messages)
		return -ENOMEM;

	ret = mxt_read_messages(data, count, messages);
	if (ret) {
		dev_err("Failed to read %u messages (%d).\n", count, ret);
		goto out;
	}
	if (!report)
		goto out;

	for (msg = messages; msg < &messages[count]; msg++) {
		mxt_dump_message(msg);
		reportid = msg->reportid;

		if (reportid == data->T6_reportid) {
			const u32 *payload = (u32*) &msg->message[0];
			u8 status = payload[0];
			data->config_csum = mxt_extract_T6_csum(&payload[1]);
			dev_dbg("Status: %02x Config Checksum: %08lx\n", status, data->config_csum);
            /* TODO: Calibration */
			//if (status == 0x00)
			//	complete(&data->auto_cal_completion);
		} else if (mxt_is_T9_message(data, msg)) {
			int id = reportid - data->T9_reportid_min;
			mxt_input_touchevent(data, msg, id);
		} else if (msg->reportid == data->T19_reportid) {
            /* TODO: Buttons */ 
			//mxt_input_button(data, msg);
		}
	}

out:
	free(messages);
	return ret;
}


/*
 * Assume a circle touch contact and use the diameter as the touch major.
 * touch_pixels = touch_channels * (max_area_pixels / max_area_channels)
 * touch_pixels = pi * (touch_major / 2) ^ 2;
 */
int get_touch_major_pixels(struct mxt_data *data, int touch_channels){
	int touch_pixels;

	if (data->max_area_channels == 0)
		return 0;

	touch_pixels = DIV_ROUND_CLOSEST(touch_channels * data->max_area_pixels,
					 data->max_area_channels);
	return int_sqrt(DIV_ROUND_CLOSEST(touch_pixels * 100, 314)) * 2;
}


void mxt_input_touchevent(struct mxt_data *data, struct mxt_message *message, int id){
	u8 status = message->message[0];
	int x;
	int y;
	int area;
	int pressure;
	int touch_major;
	int vector1, vector2;

	x = (message->message[1] << 4) | ((message->message[3] >> 4) & 0xf);
	y = (message->message[2] << 4) | ((message->message[3] & 0xf));
	if (data->max_x < 1024)
		x = x >> 2;
	if (data->max_y < 1024)
		y = y >> 2;

	area = message->message[4];
	touch_major = get_touch_major_pixels(data, area);
	pressure = message->message[5];

	/* The two vector components are 4-bit signed ints (2s complement) */
	vector1 = (signed)((signed char)message->message[6]) >> 4;
	vector2 = (signed)((signed char)(message->message[6] << 4)) >> 4;

	dev_dbg("[%u] %c%c%c%c%c%c%c%c x: %5u y: %5u area: %3u amp: %3u vector: [%d,%d]\n",
		id,
		(status & MXT_DETECT) ? 'D' : '.',
		(status & MXT_PRESS) ? 'P' : '.',
		(status & MXT_RELEASE) ? 'R' : '.',
		(status & MXT_MOVE) ? 'M' : '.',
		(status & MXT_VECTOR) ? 'V' : '.',
		(status & MXT_AMP) ? 'A' : '.',
		(status & MXT_SUPPRESS) ? 'S' : '.',
		(status & MXT_UNGRIP) ? 'U' : '.',
		x, y, area, pressure, vector1, vector2);


	//input_mt_slot(input_dev, id);
	//input_mt_report_slot_state(input_dev, MT_TOOL_FINGER,
	//			   status & MXT_DETECT);
	//data->current_id[id] = status & MXT_DETECT;

    data->report->Tip_and_InRange       = (status & MXT_PRESS)  ? 0x0 : 0x1;
    data->report->Tip_and_InRange      |= (status & MXT_DETECT) ? 0x0 : 0x3; 
    data->report->Pressure              = pressure;
    data->report->Contact_identifier    = id;
	data->report->Contact_count_max     = MXT_MAX_FINGER;	
	data->report->X 				    = x;
	data->report->Y 				    = y;
}

/*
void mxt_input_button(struct mxt_data *data, struct mxt_message *message){
	//struct device *dev = &data->client->dev;
	//struct input_dev *input = data->input_dev;
	bool button;

	// Active-low switch
	button = !(message->message[0] & MXT_GPIO3_MASK);
	//input_report_key(input, BTN_LEFT, button);
	//dev_dbg("Button state: %d\n", button);
}
*/


/* Main method called for getting data */
int mxt_handle_messages(struct mxt_data *data, bool report){
	int ret;
	u8 count;

	ret = mxt_read_num_messages(data, &count);
	if (ret) {
		dev_err("Failed to read message count (%d).\n", ret);
		return ret;
	}

	if (count > 0) {
		dev_dbg("Processing %d messages\n", count);
		ret = mxt_proc_messages(data, count, report);
    }
	else {
	    //dev_dbg("No messages\n");
	    return 0;
	}
	return ret;
}


bool mxt_object_writable(unsigned int type){
	switch (type) {
	case MXT_GEN_COMMAND_T6:
	case MXT_GEN_POWER_T7:
	case MXT_GEN_ACQUIRE_T8:
	case MXT_TOUCH_MULTI_T9:
	case MXT_TOUCH_KEYARRAY_T15:
	case MXT_TOUCH_PROXIMITY_T23:
	case MXT_TOUCH_PROXKEY_T52:
	case MXT_PROCI_GRIPFACE_T20:
	case MXT_PROCG_NOISE_T22:
	case MXT_PROCI_ONETOUCH_T24:
	case MXT_PROCI_TWOTOUCH_T27:
	case MXT_PROCI_GRIP_T40:
	case MXT_PROCI_PALM_T41:
	case MXT_PROCI_TOUCHSUPPRESSION_T42:
	case MXT_PROCI_STYLUS_T47:
	case MXT_PROCG_NOISESUPPRESSION_T48:
	case MXT_PROCI_ADAPTIVETHRESHOLD_T55:
	case MXT_PROCI_SHIELDLESS_T56:
	case MXT_PROCI_EXTRATOUCHSCREENDATA_T57:
	case MXT_PROCG_NOISESUPPRESSION_T62:
	case MXT_PROCI_LENSBENDING_T65:
	case MXT_SPT_COMMSCONFIG_T18:
	case MXT_SPT_GPIOPWM_T19:
	case MXT_SPT_SELFTEST_T25:
	case MXT_SPT_CTECONFIG_T28:
	case MXT_SPT_DIGITIZER_T43:
	case MXT_SPT_CTECONFIG_T46:
	case MXT_SPT_TIMER_T61:
		return true;
	default:
		return false;
	}
}

void mxt_dump_message(struct mxt_message *message){
	//dev_dbg("reportid: %u\tmessage: %*ph\n", message->reportid, 7, message->message);
}


inline size_t mxt_obj_size(const struct mxt_object *obj){
	return obj->size + 1;
}

inline size_t mxt_obj_instances(const struct mxt_object *obj){
	return obj->instances + 1;
}


void mxt_free_object_table(struct mxt_data *data){
	free(data->object_table);
	data->object_table = NULL;
	data->T6_reportid = 0;
	data->T9_reportid_min = 0;
	data->T9_reportid_max = 0;

}

int mxt_initialize(struct mxt_data *data){
	struct mxt_info *info = &data->info;
	int error;

	error = mxt_get_info(data);
	if (error)
		return error;

	data->object_table = malloc(info->object_num * sizeof(struct mxt_object));
	if (!data->object_table) {
		dev_err("Failed to allocate memory\n");
		return -ENOMEM;
	}

	/* Get object table information */
	error = mxt_get_object_table(data);
	if (error)
		goto err_free_object_table;

	/* Apply config from platform data */
	error = mxt_handle_pdata(data);
	if (error)
		goto err_free_object_table;

	/* Soft reset */
	error = mxt_write_object(data, MXT_GEN_COMMAND_T6,
				 MXT_COMMAND_RESET, 1);
	if (error)
		goto err_free_object_table;
	_delay_ms(MXT_RESET_TIME);
	
	dev_info("Family ID: %u Variant ID: %u Major.Minor.Build: %u.%u.%02X\n",
			info->family_id, info->variant_id, info->version >> 4,
			info->version & 0xf, info->build);

	dev_info("Matrix X Size: %u Matrix Y Size: %u Object Num: %u\n",
			info->matrix_xsize, info->matrix_ysize,
			info->object_num);
	
	error = mxt_calc_resolution(data);
	if (error)
		return error;

	return 0;

err_free_object_table:
	mxt_free_object_table(data);
	return error;


	return 0;
}

int mxt_calc_resolution(struct mxt_data *data){
	u8 orient;
	u16 xyrange[2];
	unsigned int max_x, max_y;
	u8 xylines[2];
	int ret;

	struct mxt_object *T9 = mxt_get_object(data, MXT_TOUCH_MULTI_T9);
	if (T9 == NULL)
		return -EINVAL;

	/* Get touchscreen resolution */
	ret = __mxt_read_reg(T9->start_address + MXT_TOUCH_XRANGE_LSB,
			4, xyrange);
	if (ret)
		return ret;

	ret = __mxt_read_reg(T9->start_address + MXT_TOUCH_ORIENT,
			1, &orient);
	if (ret)
		return ret;

	ret = __mxt_read_reg(T9->start_address + MXT_TOUCH_XSIZE,
			2, xylines);
	if (ret)
		return ret;

	max_x = le16_to_cpu(xyrange[0]);
	max_y = le16_to_cpu(xyrange[1]);

	if (orient & MXT_XY_SWITCH) {
		data->max_x = max_y;
		data->max_y = max_x;
	} else {
		data->max_x = max_x;
		data->max_y = max_y;
	}

	data->max_area_pixels = max_x * max_y;
	data->max_area_channels = xylines[0] * xylines[1];

	return 0;
}



int mxt_get_object_table(struct mxt_data *data){
	size_t table_size;
	int error;
	int i;
	u8 reportid;
	u32 csum[3];

	table_size = data->info.object_num * sizeof(struct mxt_object);
	error = __mxt_read_reg(MXT_OBJECT_START, table_size,
			data->object_table);
	if (error)
		return error;

	/*
	 * Read Information Block checksum from 3 bytes immediately following
	 * info block
	 */
	error = __mxt_read_reg(MXT_OBJECT_START + table_size,
			sizeof(csum), csum);
	if (error)
		return error;

	data->info_csum = csum[0] | (csum[1] << 8) | (csum[2] << 16);
	dev_info("Information Block Checksum = %06lx\n", data->info_csum);

	error = mxt_verify_info_block_csum(data);
	if (error)
		return error;

	/* Valid Report IDs start counting from 1 */
	reportid = 1;
	for (i = 0; i < data->info.object_num; i++) {
		struct mxt_object *object = data->object_table + i;
		u8 min_id, max_id;

		le16_to_cpus(&object->start_address);

		if (object->num_report_ids) {
			min_id = reportid;
			reportid += object->num_report_ids *
					mxt_obj_instances(object);
			max_id = reportid - 1;
		} else {
			min_id = 0;
			max_id = 0;
		}

		dev_dbg("Type %2d, ", 		object->type);
		dev_dbg("Start %3d, ", 		object->start_address);
		dev_dbg("Size %3d, ", 		mxt_obj_size(object));
		dev_dbg("Instances %2u, ", mxt_obj_instances(object));
		dev_dbg("ReportIDs %3u : %3u\n", min_id, max_id);

		switch (object->type) {
		case MXT_GEN_MESSAGE_T5:
			data->T5_address = object->start_address;
			break;
		case MXT_GEN_COMMAND_T6:
			data->T6_reportid = min_id;
			break;
		case MXT_TOUCH_MULTI_T9:
			data->T9_reportid_min = min_id;
			data->T9_reportid_max = max_id;
			break;
		case MXT_SPT_GPIOPWM_T19:
			data->T19_reportid = min_id;
			break;
		case MXT_SPT_MESSAGECOUNT_T44:
			data->T44_address = object->start_address;
			break;
		}
	}

	return 0;
}

int mxt_apply_pdata_config(struct mxt_data *data){
	const struct mxt_platform_data *pdata = data->pdata;
	struct mxt_object *object;
	int index = 0;
	int i, size;
	int ret;

	if (!pdata->config) {
		dev_info("No cfg data defined, skipping reg init\n");
		return 0;
	}

	for (i = 0; i < data->info.object_num; i++) {
		object = data->object_table + i;

		if (!mxt_object_writable(object->type))
			continue;

		size = mxt_obj_size(object) * mxt_obj_instances(object);
		if (index + size > pdata->config_length) {
			dev_err("Not enough config data!\n");
			return -EINVAL;
		}

		ret = __mxt_write_reg(object->start_address,
				size, &pdata->config[index]);
		if (ret){
			dev_err("Failed to apply config\n");
			return ret;
		}
		index += size;
	}

	return 0;
}

int mxt_handle_pdata(struct mxt_data *data){
	const struct mxt_platform_data *pdata = data->pdata;
	u8 voltage;
	int ret;

	ret = mxt_apply_pdata_config(data);
	if (ret)
		return ret;

	/* Set touchscreen lines */
	mxt_write_object(data, MXT_TOUCH_MULTI_T9, MXT_TOUCH_XSIZE,
			pdata->x_line);
	mxt_write_object(data, MXT_TOUCH_MULTI_T9, MXT_TOUCH_YSIZE,
			pdata->y_line);

	/* Set touchscreen orient */
	mxt_write_object(data, MXT_TOUCH_MULTI_T9, MXT_TOUCH_ORIENT,
			pdata->orient);

	/* Set touchscreen burst length */
	mxt_write_object(data, MXT_TOUCH_MULTI_T9,
			MXT_TOUCH_BLEN, pdata->blen);

	/* Set touchscreen threshold */
	mxt_write_object(data, MXT_TOUCH_MULTI_T9,
			MXT_TOUCH_TCHTHR, pdata->threshold);

	/* Set touchscreen resolution */
	mxt_write_object(data, MXT_TOUCH_MULTI_T9,
			MXT_TOUCH_XRANGE_LSB, (pdata->x_size - 1) & 0xff);
	mxt_write_object(data, MXT_TOUCH_MULTI_T9,
			MXT_TOUCH_XRANGE_MSB, (pdata->x_size - 1) >> 8);
	mxt_write_object(data, MXT_TOUCH_MULTI_T9,
			MXT_TOUCH_YRANGE_LSB, (pdata->y_size - 1) & 0xff);
	mxt_write_object(data, MXT_TOUCH_MULTI_T9,
			MXT_TOUCH_YRANGE_MSB, (pdata->y_size - 1) >> 8);

	/* Set touchscreen voltage */
	if (pdata->voltage) {
		if (pdata->voltage < MXT_VOLTAGE_DEFAULT) {
			voltage = (MXT_VOLTAGE_DEFAULT - pdata->voltage) /
				MXT_VOLTAGE_STEP;
			voltage = 0xff - voltage + 1;
		} else
			voltage = (pdata->voltage - MXT_VOLTAGE_DEFAULT) /
				MXT_VOLTAGE_STEP;

		mxt_write_object(data, MXT_SPT_CTECONFIG_T28,
				MXT_CTE_VOLTAGE, voltage);
	}

	/* Backup to memory */
	ret = mxt_write_object(data, MXT_GEN_COMMAND_T6,
			       MXT_COMMAND_BACKUPNV, MXT_BACKUP_VALUE);
	if (ret)
		return ret;
	_delay_ms(MXT_BACKUP_TIME);

	return 0;
}


/* Update 24-bit CRC with two new bytes of data */
u32 crc24_step(u32 crc, u8 byte1, u8 byte2){
	const u32 crcpoly = 0x80001b;
	u16 data = byte1 | (byte2 << 8);
	u32 result = data ^ (crc << 1);

	/* XOR result with crcpoly if bit 25 is set (overflow occurred) */
	if (result & 0x01000000)
		result ^= crcpoly;

	return result & 0x00ffffff;
}

u32 crc24(u32 crc, const u8 *data, size_t len){
	size_t i;

	for (i = 0; i < len - 1; i += 2)
		crc = crc24_step(crc, data[i], data[i + 1]);

	/* If there were an odd number of bytes pad with 0 */
	if (i < len)
		crc = crc24_step(crc, data[i], 0);

	return crc;
}

int mxt_verify_info_block_csum(struct mxt_data *data){
	size_t object_table_size, info_block_size;
	u32 crc = 0;
	u8 *info_block;
	int ret = 0;

	object_table_size = data->info.object_num * MXT_OBJECT_SIZE;
	info_block_size = sizeof(data->info) + object_table_size;
	info_block = malloc(info_block_size);
	if (!info_block)
		return -ENOMEM;

	/*
	 * Information Block CRC is computed over both ID info and Object Table
	 * So concat them in a temporary buffer, before computing CRC.
	 * TODO: refactor how the info block is read from the device such
	 * that it ends up in a single buffer and this copy is not needed.
	 */
	memcpy(info_block, &data->info, sizeof(data->info));
	memcpy(&info_block[sizeof(data->info)], data->object_table,
			object_table_size);

	crc = crc24(crc, info_block, info_block_size);

	if (crc != data->info_csum) {
		dev_err("Information Block CRC mismatch: %06lx != %06lx\n", data->info_csum, crc);
		ret = -EINVAL;
	}

	free(info_block);
	return ret;
}

int mxt_get_info(struct mxt_data *data){
	struct mxt_info *info = &data->info;
	int error;

	/* Read 7-byte info block starting at address 0 */
	error = __mxt_read_reg(MXT_INFO, sizeof(*info), info);
	if (error)
		return error;

	return 0;
}


int __mxt_read_reg(uint16_t reg, uint16_t len, void *val){
	int ret;

	ret = i2c_recv(reg, val, len);
	if (ret)
		dev_err("__mxt_read_reg(%04x, %04x, %04x) failed: %04x\n", reg, len, (unsigned int) val, ret);

	return ret;
}

int __mxt_write_reg(u16 reg, u16 len, const void *val){
	int ret;

	ret = i2c_send(reg, val, len);
	if (ret)
		dev_err("__mxt_write_reg() failed: %04x\n", ret);

	return ret;
}


int mxt_write_obj_instance(struct mxt_data *data, u8 type, u8 instance, u8 offset, u8 val){
	struct mxt_object *object;
	u16 reg;

	object = mxt_get_object(data, type);
	if (!object || offset >= mxt_obj_size(object) ||
	    instance >= mxt_obj_instances(object))
		return -EINVAL;

	reg = object->start_address + instance * mxt_obj_size(object) + offset;
	return __mxt_write_reg(reg, 1, val);
}

int mxt_write_object(struct mxt_data *data, u8 type, u8 offset, u8 val){
	
	return mxt_write_obj_instance(data, type, 0, offset, val);
}



struct mxt_object *mxt_get_object(struct mxt_data *data, u8 type){
	struct mxt_object *object;
	int i;

	for (i = 0; i < data->info.object_num; i++) {
		object = data->object_table + i;
		if (object->type == type)
			return object;
	}

	dev_err("Invalid object type\n");

	return NULL;
}



/**
 * int_sqrt - rough approximation to sqrt
 * @x: integer of which to calculate the sqrt
 *
 * A very rough approximation to the sqrt() function.
 */
#define BITS_PER_LONG 32
unsigned long int_sqrt(unsigned long x){
	unsigned long b, m, y = 0;

	if (x <= 1)
    	return x;

	m = 1UL << (BITS_PER_LONG - 2);
    while (m != 0) {
	    b = y + m;
        y >>= 1;

		if (x >= b) {
			x -= b;
			y += m;
		}
		m >>= 2;
	}
	return y;
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
    if (stat != 0x08)
        return stat;

	TWI_Write((MXT_APP_LOW<<1));		// Chip address + write
	stat = TWI_GetStatus();
    if (stat != 0x18)
        return stat;

	TWI_Write((addr & 0x00FF));			// Address low byte
	stat = TWI_GetStatus();
    if (stat != 0x28)
        return stat;

	TWI_Write((addr<<8 & 0xFF00));		// Address high byte
	stat = TWI_GetStatus();
    if (stat != 0x28)
        return stat;

	TWI_Start();						// Second start condition 	
	stat = TWI_GetStatus();
    if (stat != 0x10)
        return stat;

	TWI_Write((MXT_APP_LOW<<1) | 0x01);	// Chip address + read
	stat = TWI_GetStatus();
    if (stat != 0x40)
        return stat;

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
    if (stat != 0x08)
        return stat;

	TWI_Write((MXT_APP_LOW<<1));		// Chip address + write
	stat = TWI_GetStatus();
    if (stat != 0x18)
        return stat;

	TWI_Write((addr & 0x00FF));			// Address low byte
	stat = TWI_GetStatus();
    if (stat != 0x28)
        return stat;

	TWI_Write((addr<<8 & 0xFF00));		// Address high byte
	stat = TWI_GetStatus();
    if (stat != 0x28)
        return stat;

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



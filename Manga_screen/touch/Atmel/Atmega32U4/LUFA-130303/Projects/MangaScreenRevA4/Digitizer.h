


#ifndef _MANGA_SCREEN_DIGITIZER_H_
#define _MANGA_SCREEN_DIGITIZER_H_

#include "MangaScreen.h"
#include "i2c.h"
#include <stdlib.h>
#include <stdio.h>
	
#define le16_to_cpus(x) do { (void)(x); } while (0)

typedef uint16_t u16;
typedef unsigned long int u32;
typedef uint8_t  u8;

// Standard linux error codes
#define EPERM            1      /* Operation not permitted */
#define ENOENT           2      /* No such file or directory */
#define ESRCH            3      /* No such process */
#define EINTR            4      /* Interrupted system call */
#define EIO              5      /* I/O error */
#define ENXIO            6      /* No such device or address */
#define E2BIG            7      /* Argument list too long */
#define ENOEXEC          8      /* Exec format error */
#define EBADF            9      /* Bad file number */
#define ECHILD          10      /* No child processes */
#define EAGAIN          11      /* Try again */
#define ENOMEM          12      /* Out of memory */
#define EACCES          13      /* Permission denied */
#define EFAULT          14      /* Bad address */
#define ENOTBLK         15      /* Block device required */
#define EBUSY           16      /* Device or resource busy */
#define EEXIST          17      /* File exists */
#define EXDEV           18      /* Cross-device link */
#define ENODEV          19      /* No such device */
#define ENOTDIR         20      /* Not a directory */
#define EISDIR          21      /* Is a directory */
#define EINVAL          22      /* Invalid argument */
#define ENFILE          23      /* File table overflow */
#define EMFILE          24      /* Too many open files */
#define ENOTTY          25      /* Not a typewriter */
#define ETXTBSY         26      /* Text file busy */
#define EFBIG           27      /* File too large */
#define ENOSPC          28      /* No space left on device */
#define ESPIPE          29      /* Illegal seek */
#define EROFS           30      /* Read-only file system */
#define EMLINK          31      /* Too many links */
#define EPIPE           32      /* Broken pipe */
#define EDOM            33      /* Math argument out of domain of func */
#define ERANGE          34      /* Math result not representable */


#define CLIENT_ADDR               0x38

#define MAX_SUPPORT_POINTS		  2

#define REG_DEV_MODE		      0x00
#define REG_GEST_ID		          0x01
#define REG_TD_STATUS	          0x02
#define REG_P1_XH                 0x03
#define REG_P1_XL                 0x04
#define REG_P1_YH                 0x05
#define REG_P1_YL                 0x06
#define REG_P1_WEIGHT             0x07
#define REG_P1_MISC               0x08
#define REG_P2_XH                 0x09
#define REG_P2_XL                 0x0A
#define REG_P2_YH                 0x0B
#define REG_P2_YL                 0x0C
#define REG_P2_WEIGHT             0x0D
#define REG_P2_MISC               0x0E

#define REG_TH_GROUP              0x80

#define REG_TH_DIFF               0x85
#define REG_CTRL                  0x86
#define REG_TIMEENTERMONITOR      0x87
#define REG_PERIODACTIVE          0x88
#define REG_PERIODMONITOR         0x89

#define REG_RADIAN_VALUE          0x91
#define REG_OFFSET_LEFT_RIGHT     0x92
#define REG_OFFSET_UP_DOWN        0x93
#define REG_DISTANCE_LEFT_RIGHT   0x94
#define REG_DISTANCE_UP_DOWN      0x95
#define REG_DISTANCE_ZOOM         0x96

#define REG_LIB_VER_H             0xA1
#define REG_LIB_VER_L             0xA2
#define REG_CIPHER                0xA3
#define REG_G_MODE                0xA4
#define REG_PWR_MODE              0xA5
#define REG_FIRMID                0xA6
#define REG_FOCALTECH_ID          0xA8
#define REG_RELEASE_CODE_ID       0xAF
#define REG_STATE                 0xBC

#define EVENT_PRESS_DOWN          0x00
#define EVENT_LIFT_UP             0x01
#define EVENT_CONTACT             0x02
#define EVENT_NO_EVENT            0x03

#define REG_THRESHOLD		0x00
#define REG_REPORT_RATE	0x08
#define REG_GAIN		0x30
#define REG_OFFSET		0x31
#define REG_NUM_X		0x33
#define REG_NUM_Y		0x34

#define REG_OPMODE		0x3c
#define FACTORY_REGISTER_OPMODE		0x01

#define TOUCH_EVENT_DOWN		0x00
#define TOUCH_EVENT_UP			0x01
#define TOUCH_EVENT_ON			0x02
#define TOUCH_EVENT_RESERVED		0x03

#define EDT_SWITCH_MODE_RETRIES		10
#define EDT_SWITCH_MODE_DELAY		5 /* msec */
#define EDT_RAW_DATA_RETRIES		100
#define EDT_RAW_DATA_DELAY		1 /* msec */


/* The platform data for the touchscreen driver */
struct edt_ft5x06_platform_data {
	/* startup defaults for operational parameters */
	bool use_parameters;

    u8 threshold;
    u8 filter_coeff;
    u8 time_enter_monitor;
    u8 report_rate_active;
    u8 report_rate_monitor;
};


struct edt_ft5x06_ts_data {
	u16 num_x;
	u16 num_y;

	//struct mutex mutex;
	bool factory_mode;
    int threshold;
    int filter_coeff;
    int time_enter_monitor;
    int report_rate_active;
    int report_rate_monitor;

	char name[16];
	char fw_version[16];
};

struct touch_point {
    u16 x;
    u16 y;
    u8 weight;
    u8 area;
    u8 event;
    u8 id;
    u8 reported;
    u8 notseen;
};

int digitizer_set_config(int config);
int digitizer_get_report(USB_DigitizerReport_Data_t* report);
int digitizer_get_num_touches(void);

int edt_ft5x06_get_data(void);
int edt_ft5x06_ts_identify(struct edt_ft5x06_ts_data *tsdata);
int digitizer_init(void);
int edt_ft5x06_ts_readwrite(u16 wr_len, u8 *wr_buf, u16 rd_len, u8 *rd_buf);
int edt_ft5x06_register_write(struct edt_ft5x06_ts_data *tsdata, u8 addr, u8 value);
int edt_ft5x06_register_read(struct edt_ft5x06_ts_data *tsdata, u8 addr);

#endif

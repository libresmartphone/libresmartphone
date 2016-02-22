


#ifndef _MANGA_SCREEN_DIGITIZER_H_
#define _MANGA_SCREEN_DIGITIZER_H_

#include "MangaScreen.h"
#include <stdlib.h>
#include <stdio.h>
	
#define le16_to_cpus(x) do { (void)(x); } while (0)

/*
 * Divide positive or negative dividend by positive divisor and round
 * to closest integer. Result is undefined for negative divisors and
 * for negative dividends if the divisor variable type is unsigned.
 */
#define DIV_ROUND_CLOSEST(x, divisor)(                  \
{                                                       \
        typeof(x) __x = x;                              \
        typeof(divisor) __d = divisor;                  \
        (((typeof(x))-1) > 0 ||                         \
         ((typeof(divisor))-1) > 0 || (__x) > 0) ?      \
                (((__x) + ((__d) / 2)) / (__d)) :       \
                (((__x) - ((__d) / 2)) / (__d));        \
}                                                       \
)


typedef uint16_t u16;
typedef unsigned long int u32;
typedef uint8_t  u8;

unsigned long int_sqrt(unsigned long x);

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

#define IRQF_TRIGGER_FALLING    0x00000002

/* Version */
#define MXT_VER_20		20
#define MXT_VER_21		21
#define MXT_VER_22		22

/* Slave addresses */
#define MXT_APP_LOW		0x4a
#define MXT_APP_HIGH		0x4b
/*
 * MXT_BOOT_LOW disagrees with Atmel documentation, but has been
 * updated to support new touch hardware that pairs 0x26 boot with 0x4a app.
 */
#define MXT_BOOT_LOW		0x26
#define MXT_BOOT_HIGH		0x25

/* Firmware */
#define MXT_FW_NAME		"maxtouch.fw"

/* Config file */
#define MXT_CONFIG_NAME		"maxtouch.cfg"

/* Configuration Data */
#define MXT_CONFIG_VERSION	"OBP_RAW V1"

/* Registers */
#define MXT_INFO		0x00
#define MXT_FAMILY_ID		0x00
#define MXT_VARIANT_ID		0x01
#define MXT_VERSION		0x02
#define MXT_BUILD		0x03
#define MXT_MATRIX_X_SIZE	0x04
#define MXT_MATRIX_Y_SIZE	0x05
#define MXT_OBJECT_NUM		0x06
#define MXT_OBJECT_START	0x07

#define MXT_OBJECT_SIZE		6

/* Object types */
#define MXT_DEBUG_DIAGNOSTIC_T37	37
#define MXT_GEN_MESSAGE_T5		5
#define MXT_GEN_COMMAND_T6		6
#define MXT_GEN_POWER_T7		7
#define MXT_GEN_ACQUIRE_T8		8
#define MXT_GEN_DATASOURCE_T53		53
#define MXT_TOUCH_MULTI_T9		9
#define MXT_TOUCH_KEYARRAY_T15		15
#define MXT_TOUCH_PROXIMITY_T23		23
#define MXT_TOUCH_PROXKEY_T52		52
#define MXT_PROCI_GRIPFACE_T20		20
#define MXT_PROCG_NOISE_T22		22
#define MXT_PROCI_ONETOUCH_T24		24
#define MXT_PROCI_TWOTOUCH_T27		27
#define MXT_PROCI_GRIP_T40		40
#define MXT_PROCI_PALM_T41		41
#define MXT_PROCI_TOUCHSUPPRESSION_T42	42
#define MXT_PROCI_STYLUS_T47		47
#define MXT_PROCG_NOISESUPPRESSION_T48	48
#define MXT_PROCI_ADAPTIVETHRESHOLD_T55 55
#define MXT_PROCI_SHIELDLESS_T56	56
#define MXT_PROCI_EXTRATOUCHSCREENDATA_T57	57
#define MXT_PROCG_NOISESUPPRESSION_T62	62
#define MXT_PROCI_LENSBENDING_T65	65
#define MXT_SPT_COMMSCONFIG_T18		18
#define MXT_SPT_GPIOPWM_T19		19
#define MXT_SPT_SELFTEST_T25		25
#define MXT_SPT_CTECONFIG_T28		28
#define MXT_SPT_USERDATA_T38		38
#define MXT_SPT_DIGITIZER_T43		43
#define MXT_SPT_MESSAGECOUNT_T44	44
#define MXT_SPT_CTECONFIG_T46		46
#define MXT_SPT_TIMER_T61		61

/* MXT_GEN_COMMAND_T6 field */
#define MXT_COMMAND_RESET	0
#define MXT_COMMAND_BACKUPNV	1
#define MXT_COMMAND_CALIBRATE	2
#define MXT_COMMAND_REPORTALL	3
#define MXT_COMMAND_DIAGNOSTIC	5

#define MXT_T6_CMD_PAGE_UP		0x01
#define MXT_T6_CMD_PAGE_DOWN		0x02
#define MXT_T6_CMD_DELTAS		0x10
#define MXT_T6_CMD_REFS			0x11
#define MXT_T6_CMD_DEVICE_ID		0x80
#define MXT_T6_CMD_TOUCH_THRESH		0xF4

/* MXT_GEN_POWER_T7 field */
#define MXT_POWER_IDLEACQINT	0
#define MXT_POWER_ACTVACQINT	1
#define MXT_POWER_ACTV2IDLETO	2

/* MXT_GEN_ACQUIRE_T8 field */
#define MXT_ACQUIRE_CHRGTIME	0
#define MXT_ACQUIRE_TCHDRIFT	2
#define MXT_ACQUIRE_DRIFTST	3
#define MXT_ACQUIRE_TCHAUTOCAL	4
#define MXT_ACQUIRE_SYNC	5
#define MXT_ACQUIRE_ATCHCALST	6
#define MXT_ACQUIRE_ATCHCALSTHR	7

/* MXT_TOUCH_MULTI_T9 field */
#define MXT_TOUCH_CTRL		0
#define MXT_TOUCH_XORIGIN	1
#define MXT_TOUCH_YORIGIN	2
#define MXT_TOUCH_XSIZE		3
#define MXT_TOUCH_YSIZE		4
#define MXT_TOUCH_BLEN		6
#define MXT_TOUCH_TCHTHR	7
#define MXT_TOUCH_TCHDI		8
#define MXT_TOUCH_ORIENT	9
#define MXT_TOUCH_MOVHYSTI	11
#define MXT_TOUCH_MOVHYSTN	12
#define MXT_TOUCH_NUMTOUCH	14
#define MXT_TOUCH_MRGHYST	15
#define MXT_TOUCH_MRGTHR	16
#define MXT_TOUCH_AMPHYST	17
#define MXT_TOUCH_XRANGE_LSB	18
#define MXT_TOUCH_XRANGE_MSB	19
#define MXT_TOUCH_YRANGE_LSB	20
#define MXT_TOUCH_YRANGE_MSB	21
#define MXT_TOUCH_XLOCLIP	22
#define MXT_TOUCH_XHICLIP	23
#define MXT_TOUCH_YLOCLIP	24
#define MXT_TOUCH_YHICLIP	25
#define MXT_TOUCH_XEDGECTRL	26
#define MXT_TOUCH_XEDGEDIST	27
#define MXT_TOUCH_YEDGECTRL	28
#define MXT_TOUCH_YEDGEDIST	29
#define MXT_TOUCH_JUMPLIMIT	30

/* MXT_TOUCH_CTRL bits */
#define MXT_TOUCH_CTRL_ENABLE	(1 << 0)
#define MXT_TOUCH_CTRL_RPTEN	(1 << 1)
#define MXT_TOUCH_CTRL_DISAMP	(1 << 2)
#define MXT_TOUCH_CTRL_DISVECT	(1 << 3)
#define MXT_TOUCH_CTRL_DISMOVE	(1 << 4)
#define MXT_TOUCH_CTRL_DISREL	(1 << 5)
#define MXT_TOUCH_CTRL_DISPRESS	(1 << 6)
#define MXT_TOUCH_CTRL_SCANEN	(1 << 7)
#define MXT_TOUCH_CTRL_OPERATIONAL	(MXT_TOUCH_CTRL_ENABLE | \
					 MXT_TOUCH_CTRL_SCANEN | \
					 MXT_TOUCH_CTRL_RPTEN)
#define MXT_TOUCH_CTRL_SCANNING		(MXT_TOUCH_CTRL_ENABLE | \
					 MXT_TOUCH_CTRL_SCANEN)
#define MXT_TOUCH_CTRL_OFF		0x0

/* MXT_PROCI_GRIPFACE_T20 field */
#define MXT_GRIPFACE_CTRL	0
#define MXT_GRIPFACE_XLOGRIP	1
#define MXT_GRIPFACE_XHIGRIP	2
#define MXT_GRIPFACE_YLOGRIP	3
#define MXT_GRIPFACE_YHIGRIP	4
#define MXT_GRIPFACE_MAXTCHS	5
#define MXT_GRIPFACE_SZTHR1	7
#define MXT_GRIPFACE_SZTHR2	8
#define MXT_GRIPFACE_SHPTHR1	9
#define MXT_GRIPFACE_SHPTHR2	10
#define MXT_GRIPFACE_SUPEXTTO	11

/* MXT_PROCI_NOISE field */
#define MXT_NOISE_CTRL		0
#define MXT_NOISE_OUTFLEN	1
#define MXT_NOISE_GCAFUL_LSB	3
#define MXT_NOISE_GCAFUL_MSB	4
#define MXT_NOISE_GCAFLL_LSB	5
#define MXT_NOISE_GCAFLL_MSB	6
#define MXT_NOISE_ACTVGCAFVALID	7
#define MXT_NOISE_NOISETHR	8
#define MXT_NOISE_FREQHOPSCALE	10
#define MXT_NOISE_FREQ0		11
#define MXT_NOISE_FREQ1		12
#define MXT_NOISE_FREQ2		13
#define MXT_NOISE_FREQ3		14
#define MXT_NOISE_FREQ4		15
#define MXT_NOISE_IDLEGCAFVALID	16

/* MXT_SPT_COMMSCONFIG_T18 */
#define MXT_COMMS_CTRL		0
#define MXT_COMMS_CMD		1

/* MXT_SPT_CTECONFIG_T28 field */
#define MXT_CTE_CTRL		0
#define MXT_CTE_CMD		1
#define MXT_CTE_MODE		2
#define MXT_CTE_IDLEGCAFDEPTH	3
#define MXT_CTE_ACTVGCAFDEPTH	4
#define MXT_CTE_VOLTAGE		5

#define MXT_VOLTAGE_DEFAULT	2700000
#define MXT_VOLTAGE_STEP	10000

/* Define for MXT_GEN_COMMAND_T6 */
#define MXT_BOOT_VALUE		0xa5
#define MXT_BACKUP_VALUE	0x55
#define MXT_BACKUP_TIME		270	/* msec */
#define MXT_RESET_TIME		350	/* msec */
#define MXT_CAL_TIME		25	/* msec */

#define MXT_FWRESET_TIME	500	/* msec */

/* Default value for acquisition interval when in suspend mode*/
#define MXT_SUSPEND_ACQINT_VALUE 32      /* msec */

/* MXT_SPT_GPIOPWM_T19 field */
#define MXT_GPIO0_MASK		0x04
#define MXT_GPIO1_MASK		0x08
#define MXT_GPIO2_MASK		0x10
#define MXT_GPIO3_MASK		0x20

/* Command to unlock bootloader */
#define MXT_UNLOCK_CMD_MSB	0xaa
#define MXT_UNLOCK_CMD_LSB	0xdc

/* Bootloader mode status */
#define MXT_WAITING_BOOTLOAD_CMD	0xc0	/* valid 7 6 bit only */
#define MXT_WAITING_FRAME_DATA	0x80	/* valid 7 6 bit only */
#define MXT_FRAME_CRC_CHECK	0x02
#define MXT_FRAME_CRC_FAIL	0x03
#define MXT_FRAME_CRC_PASS	0x04
#define MXT_APP_CRC_FAIL	0x40	/* valid 7 8 bit only */
#define MXT_BOOT_STATUS_MASK	0x3f

/* Touch status */
#define MXT_UNGRIP		(1 << 0)
#define MXT_SUPPRESS		(1 << 1)
#define MXT_AMP			(1 << 2)
#define MXT_VECTOR		(1 << 3)
#define MXT_MOVE		(1 << 4)
#define MXT_RELEASE		(1 << 5)
#define MXT_PRESS		(1 << 6)
#define MXT_DETECT		(1 << 7)

/* Touch orient bits */
#define MXT_XY_SWITCH		(1 << 0)
#define MXT_X_INVERT		(1 << 1)
#define MXT_Y_INVERT		(1 << 2)

/* Touchscreen absolute values */
#define MXT_MAX_AREA		0xff

#define MXT_MAX_FINGER		10

/* For CMT (must match XRANGE/YRANGE as defined in board config */
#define MXT_PIXELS_PER_MM	20


/* Orient */
#define MXT_NORMAL		0x0
#define MXT_DIAGONAL		0x1
#define MXT_HORIZONTAL_FLIP	0x2
#define MXT_ROTATED_90_COUNTER	0x3
#define MXT_VERTICAL_FLIP	0x4
#define MXT_ROTATED_90		0x5
#define MXT_ROTATED_180		0x6
#define MXT_DIAGONAL_COUNTER	0x7

/* The platform data for the Atmel maXTouch touchscreen driver */
struct mxt_platform_data {
	const u8 *config;
	size_t config_length;

	unsigned int x_line;
	unsigned int y_line;
	unsigned int x_size;
	unsigned int y_size;
	unsigned int blen;
	unsigned int threshold;
	unsigned long voltage;
	unsigned char orient;
	unsigned long irqflags;
};


struct mxt_cfg_file_hdr {
	bool valid;
	u32 info_crc;
	u32 cfg_crc;
};

struct mxt_cfg_file_line {
	//struct list_head list;
	u16 addr;
	u8 size;
	u8 *content;
};

struct mxt_info {
	u8 family_id;
	u8 variant_id;
	u8 version;
	u8 build;
	u8 matrix_xsize;
	u8 matrix_ysize;
	u8 object_num;
};

struct mxt_object {
	u8 type;
	u16 start_address;
	u8 size;		/* Size of each instance - 1 */
	u8 instances;		/* Number of instances - 1 */
	u8 num_report_ids;
} __packed;

struct mxt_message {
	u8 reportid;
	u8 message[7];
};

/* Each client has this additional data */
struct mxt_data {
	//struct i2c_client *client;
	//struct input_dev *input_dev;
	USB_DigitizerReport_Data_t* report;
	char phys[64];		/* device physical location */
	const struct mxt_platform_data *pdata;
	struct mxt_object *object_table;
	struct mxt_info info;
	bool is_tp;
	bool initialized; 

	unsigned int irq;
	unsigned int max_x;
	unsigned int max_y;

	/* max touchscreen area in terms of pixels and channels */
	unsigned int max_area_pixels;
	unsigned int max_area_channels;

	u32 info_csum;
	u32 config_csum;

	/* Cached parameters from object table */
	u16 T5_address;
	u8 T6_reportid;
	u8 T9_reportid_min;
	u8 T9_reportid_max;
	u8 T19_reportid;
	u16 T44_address;

	/* for fw update in bootloader */
	//struct completion bl_completion;

	/* per-instance debugfs root */
	//struct dentry *dentry_dev;
	//struct dentry *dentry_deltas;
	//struct dentry *dentry_refs;
	//struct dentry *dentry_object;

	/* Protect access to the T37 object buffer, used by debugfs */
	//struct mutex T37_buf_mutex;
	//u8 *T37_buf;
	//size_t T37_buf_size;

	/* Saved T7 configuration
	 * [0] = IDLEACQINT
	 * [1] = ACTVACQINT
	 * [2] = ACTV2IDLETO
	 */
	u8 T7_config[3];
	bool T7_config_valid;

	/* T7 IDLEACQINT & ACTVACQINT setting when in suspend mode*/
	u8 suspend_acq_interval;

	/* Saved T9 Ctrl field */
	u8 T9_ctrl;
	bool T9_ctrl_valid;

	bool irq_wake;  /* irq wake is enabled */
	/* Saved T42 Touch Suppression field */
	u8 T42_ctrl;
	bool T42_ctrl_valid;

	/* Saved T19 GPIO config */
	u8 T19_ctrl;
	bool T19_ctrl_valid;

	/* Protect access to the object register buffer */
	//struct mutex object_str_mutex;
	char *object_str;
	size_t object_str_size;

	/* for auto-calibration in suspend */
	//struct completion auto_cal_completion;

	/* firmware file name */
	char *fw_file;

	/* config file name */
	char *config_file;

	/* map for the tracking id currently being used */
	bool current_id[MXT_MAX_FINGER];
};


int Digitizer_Init(void);
//int Digitizer_get_report(void);
int Digitizer_get_report(USB_DigitizerReport_Data_t* DigitizerReport);

bool mxt_object_writable(unsigned int type);
void mxt_dump_message(struct mxt_message *message);

unsigned mxt_extract_T6_csum(const u32 *csum);

void mxt_input_touchevent(struct mxt_data *data, struct mxt_message *message, int id);
void mxt_input_button(struct mxt_data *data, struct mxt_message *message);

u32 crc24_step(u32 crc, u8 byte1, u8 byte2);
u32 crc24(u32 crc, const u8 *data, size_t len);
int mxt_verify_info_block_csum(struct mxt_data *data);
int mxt_get_info(struct mxt_data *data);
void mxt_free_object_table(struct mxt_data *data);
int mxt_initialize(struct mxt_data *data);
int mxt_calc_resolution(struct mxt_data *data);
int mxt_get_object_table(struct mxt_data *data);
struct mxt_object *mxt_get_object(struct mxt_data *data, u8 type);

int mxt_handle_messages(struct mxt_data *data, bool report);

int mxt_read_num_messages(struct mxt_data *data, u8 *count);

int mxt_apply_pdata_config(struct mxt_data *data);
int mxt_handle_pdata(struct mxt_data *data);

int mxt_write_obj_instance(struct mxt_data *data, u8 type, u8 instance, u8 offset, u8 val);
int mxt_write_object(struct mxt_data *data, u8 type, u8 offset, u8 val);

// Level 2 
int __mxt_read_reg(uint16_t reg, uint16_t len, void *val);
int __mxt_write_reg(u16 reg, u16 len, const void *val);

int i2c_recv(uint16_t addr, uint8_t *buf, int count);
int i2c_send(uint16_t addr, const uint8_t *buf, int count);

// Level 1 
void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(uint8_t u8data);
uint8_t TWI_Read(char ack);
uint8_t TWI_GetStatus(void);

#endif

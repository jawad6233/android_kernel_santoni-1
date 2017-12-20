/*
 *
 * FocalTech ft5x06 TouchScreen driver.
 *
 * Copyright (c) 2010  Focal tech Ltd.
 * Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 * Copyright (C) 2016 XiaoMi, Inc.
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
 */
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/firmware.h>
#include <linux/debugfs.h>
#include <linux/input/ft5x06_720p.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
<<<<<<< HEAD
=======
#ifdef CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE
#include <linux/input/doubletap2wake.h>
#endif
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207

#if CTP_CHARGER_DETECT
#include <linux/power_supply.h>
#endif

#if defined(CONFIG_FB)
#include <linux/notifier.h>
#include <linux/fb.h>

#elif defined(CONFIG_HAS_EARLYSUSPEND)
#include <linux/earlysuspend.h>
/* Early-suspend level */
#define FT_SUSPEND_LEVEL 1
#endif

<<<<<<< HEAD
u8 TP_Maker, LCD_Maker;
=======
#if CTP_PROC_INTERFACE
#include "ft5x06_test_lib.h"
#endif

#if CTP_LOCKDOWN_INFO
static u8 lockdown_info[FT_LOCKDOWN_SIZE];
extern u8 tp_color;
#endif

static u8 TP_Maker, LCD_Maker;
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207

#define FT_DEBUG_DIR_NAME   "ts_debug"

#define TPD_MAX_POINTS_5	5
#define TPD_MAX_POINTS_10   10

#define TPD_MAX_POINTS_2	2
#define AUTO_CLB_NEED   1
#define AUTO_CLB_NONEED	 0
<<<<<<< HEAD
=======
static struct Upgrade_Info fts_updateinfo[] = {
	{0x55, "FT5x06", TPD_MAX_POINTS_5, AUTO_CLB_NEED, 50, 30, 0x79, 0x03, 1,
	 2000},
	{0x08, "FT5606", TPD_MAX_POINTS_5, AUTO_CLB_NEED, 50, 30, 0x79, 0x06,
	 100, 2000},
	{0x0a, "FT5x16", TPD_MAX_POINTS_5, AUTO_CLB_NEED, 50, 30, 0x79, 0x07, 1,
	 1500},
	{0x05, "FT6208", TPD_MAX_POINTS_2, AUTO_CLB_NONEED, 60, 30, 0x79, 0x05,
	 10, 2000},
	{0x06, "FT6x06", TPD_MAX_POINTS_2, AUTO_CLB_NONEED, 100, 30, 0x79, 0x08,
	 10, 2000},
	{0x36, "FT6x36", TPD_MAX_POINTS_2, AUTO_CLB_NONEED, 100, 30, 0x79, 0x18, 10, 2000},
	{0x55, "FT5x06i", TPD_MAX_POINTS_5, AUTO_CLB_NEED, 50, 30, 0x79, 0x03,
	 1, 2000},
	{0x14, "FT5336", TPD_MAX_POINTS_10, AUTO_CLB_NONEED, 30, 30, 0x79, 0x11,
	 10, 2000},
	{0x13, "FT3316", TPD_MAX_POINTS_5, AUTO_CLB_NONEED, 30, 30, 0x79, 0x11,
	 10, 2000},
	{0x12, "FT5436i", TPD_MAX_POINTS_5, AUTO_CLB_NONEED, 30, 30, 0x79, 0x11,
	 10, 2000},
	{0x11, "FT5336i", TPD_MAX_POINTS_5, AUTO_CLB_NONEED, 30, 30, 0x79, 0x11,
	 10, 2000},
};
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207

#define FT_STORE_TS_INFO(buf, id, name, max_tch, group_id, fw_vkey_support, \
			fw_name, fw_maj, fw_min, fw_sub_min) \
			snprintf(buf, FT_INFO_MAX_LEN, \
				"controller\t= focaltech\n" \
				"model\t\t= 0x%x\n" \
				"name\t\t= %s\n" \
				"max_touches\t= %d\n" \
				"drv_ver\t\t= 0x%x\n" \
				"group_id\t= 0x%x\n" \
				"fw_vkey_support\t= %s\n" \
				"fw_name\t\t= %s\n" \
				"fw_ver\t\t= %d.%d.%d\n", id, name, \
				max_tch, FT_DRIVER_VERSION, group_id, \
				fw_vkey_support, fw_name, fw_maj, fw_min, \
				fw_sub_min)
<<<<<<< HEAD

=======
#if CTP_PROC_INTERFACE
#define CTP_PARENT_PROC_NAME  "touchscreen"
#define CTP_OPEN_PROC_NAME        "ctp_openshort_test"
#define CTP_LOCKDOWN_INFOR_NAME   "lockdown_info"

static struct semaphore g_device_mutex;

static ssize_t ctp_open_proc_read(struct file *file, char __user *buf,
				  size_t count, loff_t *ppos);
static ssize_t ctp_open_proc_write(struct file *filp,
				   const char __user *userbuf, size_t count,
				   loff_t *ppos);
static const struct file_operations ctp_open_procs_fops = {
	.write = ctp_open_proc_write,
	.read = ctp_open_proc_read,
	.owner = THIS_MODULE,
};

static ssize_t ctp_lockdown_proc_read(struct file *file, char __user *buf,
				      size_t count, loff_t *ppos);
static ssize_t ctp_lockdown_proc_write(struct file *filp,
				       const char __user *userbuf,
				       size_t count, loff_t *ppos);
static const struct file_operations ctp_lockdown_procs_fops = {
	.write = ctp_lockdown_proc_write,
	.read = ctp_lockdown_proc_read,
	.owner = THIS_MODULE,
};

#endif

#if FTS_PROC_APK_DEBUG
#define PROC_UPGRADE			0
#define PROC_READ_REGISTER		1
#define PROC_WRITE_REGISTER	2
#define PROC_RAWDATA			3
#define PROC_AUTOCLB			4

#define PROC_NAME	"ft5x0x-debug"
static unsigned char proc_operate_mode = PROC_RAWDATA;
static struct proc_dir_entry *ft5x0x_proc_entry;
#endif

static u8 is_ic_update_crash;
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
static struct i2c_client *update_client;

#if CTP_CHARGER_DETECT
extern int power_supply_get_battery_charge_state(struct power_supply *psy);
static struct power_supply	*batt_psy;
static u8 is_charger_plug;
static u8 pre_charger_status;
<<<<<<< HEAD

#endif




=======
#endif

#if CTP_PROC_INTERFACE
static struct i2c_client *g_focalclient;
#endif
#if CTP_PROC_INTERFACE
static int focal_i2c_Read(unsigned char *writebuf,
			  int writelen, unsigned char *readbuf, int readlen)
{
	int ret;

	if (writelen > 0) {
		struct i2c_msg msgs[] = {
			{
			 .addr = g_focalclient->addr,
			 .flags = 0,
			 .len = writelen,
			 .buf = writebuf,
			 },
			{
			 .addr = g_focalclient->addr,
			 .flags = I2C_M_RD,
			 .len = readlen,
			 .buf = readbuf,
			 },
		};
		ret = i2c_transfer(g_focalclient->adapter, msgs, 2);
		if (ret < 0)
			dev_err(&g_focalclient->dev, "f%s: i2c read error.\n",
				__func__);
	} else {
		struct i2c_msg msgs[] = {
			{
			 .addr = g_focalclient->addr,
			 .flags = I2C_M_RD,
			 .len = readlen,
			 .buf = readbuf,
			 },
		};
		ret = i2c_transfer(g_focalclient->adapter, msgs, 1);
		if (ret < 0)
			dev_err(&g_focalclient->dev, "%s:i2c read error.\n",
				__func__);
	}
	return ret;
}

/*write data by i2c*/
static int focal_i2c_Write(unsigned char *writebuf, int writelen)
{
	int ret;

	struct i2c_msg msg[] = {
		{
		 .addr = g_focalclient->addr,
		 .flags = 0,
		 .len = writelen,
		 .buf = writebuf,
		 },
	};

	ret = i2c_transfer(g_focalclient->adapter, msg, 1);
	if (ret < 0)
		dev_err(&g_focalclient->dev, "%s i2c write error.\n", __func__);

	return ret;
}
#endif
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207

static int ft5x06_i2c_read(struct i2c_client *client, char *writebuf,
						   int writelen, char *readbuf, int readlen)
{
	int ret;

	if (writelen > 0) {
		struct i2c_msg msgs[] = {
			{
				.addr = client->addr,
				.flags = 0,
				.len = writelen,
				.buf = writebuf,
<<<<<<< HEAD
			},
=======
			},	
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
			{
				.addr = client->addr,
				.flags = I2C_M_RD,
				.len = readlen,
				.buf = readbuf,
			},
		};
		ret = i2c_transfer(client->adapter, msgs, 2);
		if (ret < 0)
<<<<<<< HEAD
			dev_err(&client->dev, "%s: i2c read error.\n", __func__);
=======
		dev_err(&client->dev, "%s: i2c read error.\n", __func__);
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
	} else {
		struct i2c_msg msgs[] = {
			{
				.addr = client->addr,
				.flags = I2C_M_RD,
				.len = readlen,
				.buf = readbuf,
			},
		};
		ret = i2c_transfer(client->adapter, msgs, 1);
		if (ret < 0)
			dev_err(&client->dev, "%s:i2c read error.\n", __func__);
	}
	return ret;
}

static int ft5x06_i2c_write(struct i2c_client *client, char *writebuf,
							int writelen)
{
	int ret;

	struct i2c_msg msgs[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.len = writelen,
			.buf = writebuf,
		},
	};
	ret = i2c_transfer(client->adapter, msgs, 1);
	if (ret < 0)
		dev_err(&client->dev, "%s: i2c write error.\n", __func__);

	return ret;
}

static int ft5x0x_write_reg(struct i2c_client *client, u8 addr, const u8 val)
{
	u8 buf[2] = {0};

	buf[0] = addr;
	buf[1] = val;

	return ft5x06_i2c_write(client, buf, sizeof(buf));
}

<<<<<<< HEAD
=======
static int ft5x0x_read_reg(struct i2c_client *client, u8 addr, u8 *val)
{
	return ft5x06_i2c_read(client, &addr, 1, val, 1);
}

>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
static void ft5x06_update_fw_vendor_id(struct ft5x06_ts_data *data)
{
	struct i2c_client *client = data->client;
	u8 reg_addr;
	int err;

	reg_addr = FT_REG_FW_VENDOR_ID;
	err = ft5x06_i2c_read(client, &reg_addr, 1, &data->fw_vendor_id, 1);
	if (err < 0)
		dev_err(&client->dev, "fw vendor id read failed");
}

<<<<<<< HEAD
=======
static void ft5x06_update_fw_ver(struct ft5x06_ts_data *data)
{
	struct i2c_client *client = data->client;
	u8 reg_addr;
	int err;

	reg_addr = FT_REG_FW_VER;
	err = ft5x06_i2c_read(client, &reg_addr, 1, &data->fw_ver[0], 1);
	if (err < 0)
		dev_err(&client->dev, "fw major version read failed");

	reg_addr = FT_REG_FW_MIN_VER;
	err = ft5x06_i2c_read(client, &reg_addr, 1, &data->fw_ver[1], 1);
	if (err < 0)
		dev_err(&client->dev, "fw minor version read failed");

	reg_addr = FT_REG_FW_SUB_MIN_VER;
	err = ft5x06_i2c_read(client, &reg_addr, 1, &data->fw_ver[2], 1);
	if (err < 0)
		dev_err(&client->dev, "fw sub minor version read failed");

	dev_info(&client->dev, "Firmware version = %d.%d.%d\n",
		 data->fw_ver[0], data->fw_ver[1], data->fw_ver[2]);
}

>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
static irqreturn_t ft5x06_ts_interrupt(int irq, void *dev_id)
{
	struct ft5x06_ts_data *data = dev_id;
	struct input_dev *ip_dev;
	int rc, i;
	u32 id, x, y, status, num_touches;
	u8 reg = 0x00, *buf;
	bool update_input = false;

	if (!data) {
		CTP_ERROR("%s: Invalid data\n", __func__);
		return IRQ_HANDLED;
	}

#if CTP_CHARGER_DETECT
<<<<<<< HEAD
	if (!batt_psy)

		batt_psy = power_supply_get_by_name("usb");
	else {
=======
	if (!batt_psy) {

		batt_psy = power_supply_get_by_name("usb");
	} else {
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
		is_charger_plug = (u8)power_supply_get_battery_charge_state(batt_psy);

		if (is_charger_plug != pre_charger_status) {
			pre_charger_status = is_charger_plug;
			ft5x0x_write_reg(update_client, 0x8B, is_charger_plug);

		}
	}

#endif

	ip_dev = data->input_dev;
	buf = data->tch_data;

<<<<<<< HEAD
	rc = ft5x06_i2c_read(data->client, &reg, 1,
						 buf, data->tch_data_len);
=======
	rc = ft5x06_i2c_read(data->client, &reg, 1, buf, data->tch_data_len);
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
	if (rc < 0) {
		dev_err(&data->client->dev, "%s: read data fail\n", __func__);
		return IRQ_HANDLED;
	}

	for (i = 0; i < data->pdata->num_max_touches; i++) {
		id = (buf[FT_TOUCH_ID_POS + FT_ONE_TCH_LEN * i]) >> 4;
		if (id >= FT_MAX_ID)
			break;

		update_input = true;

		x = (buf[FT_TOUCH_X_H_POS + FT_ONE_TCH_LEN * i] & 0x0F) << 8 |
			(buf[FT_TOUCH_X_L_POS + FT_ONE_TCH_LEN * i]);
		y = (buf[FT_TOUCH_Y_H_POS + FT_ONE_TCH_LEN * i] & 0x0F) << 8 |
			(buf[FT_TOUCH_Y_L_POS + FT_ONE_TCH_LEN * i]);

		status = buf[FT_TOUCH_EVENT_POS + FT_ONE_TCH_LEN * i] >> 6;

		num_touches = buf[FT_TD_STATUS] & FT_STATUS_NUM_TP_MASK;

		/* invalid combination */
		if (!num_touches && !status && !id)
			break;

		if (y == 2000) {
<<<<<<< HEAD
=======
			#ifdef CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE
			if(dt2w_switch && dt2w_scr_suspended) return IRQ_HANDLED;
			#endif
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
			y = 1344;

			switch (x) {
			case 180:
				x = 150;
				break;
			case 540:
				x = 360;
				break;
			case 900:
				x = 580;
				break;
			default:
				break;
			}
<<<<<<< HEAD
=======

>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
		}

		input_mt_slot(ip_dev, id);
		if (status == FT_TOUCH_DOWN || status == FT_TOUCH_CONTACT) {
			input_mt_report_slot_state(ip_dev, MT_TOOL_FINGER, 1);
			input_report_abs(ip_dev, ABS_MT_POSITION_X, x);
			input_report_abs(ip_dev, ABS_MT_POSITION_Y, y);
		} else {
			input_mt_report_slot_state(ip_dev, MT_TOOL_FINGER, 0);
		}
	 }

	if (update_input) {
		input_mt_report_pointer_emulation(ip_dev, false);
		input_sync(ip_dev);
	}

	if (num_touches == 0) {
		 for (i = 0; i < data->pdata->num_max_touches; i++) {
			input_mt_slot(ip_dev, i);
			input_mt_report_slot_state(ip_dev, MT_TOOL_FINGER, 0);
		}
		input_mt_report_pointer_emulation(ip_dev, false);
		input_sync(ip_dev);
	}
	return IRQ_HANDLED;
}

static int ft5x06_power_on(struct ft5x06_ts_data *data, bool on)
{
	int rc;

<<<<<<< HEAD
	if (!on)
		goto power_off;
=======
	if (!on) {
		goto power_off;
	}
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207

	rc = regulator_enable(data->vdd);
	if (rc) {
		dev_err(&data->client->dev,
				"Regulator vdd enable failed rc=%d\n", rc);
		return rc;
	}

	rc = regulator_enable(data->vcc_i2c);
	if (rc) {
		dev_err(&data->client->dev,
				"Regulator vcc_i2c enable failed rc=%d\n", rc);
		regulator_disable(data->vdd);
	}

	return rc;

power_off:
	rc = regulator_disable(data->vdd);
	if (rc) {
		dev_err(&data->client->dev,
				"Regulator vdd disable failed rc=%d\n", rc);
		return rc;
	}

	rc = regulator_disable(data->vcc_i2c);
	if (rc) {
		dev_err(&data->client->dev,
				"Regulator vcc_i2c disable failed rc=%d\n", rc);
		rc = regulator_enable(data->vdd);
		if (rc) {
			dev_err(&data->client->dev,
					"Regulator vdd enable failed rc=%d\n", rc);
		}
	}

	return rc;
}

static int ft5x06_power_init(struct ft5x06_ts_data *data, bool on)
{
	int rc;

	if (!on)
		goto pwr_deinit;

	data->vdd = regulator_get(&data->client->dev, "vdd");
	if (IS_ERR(data->vdd)) {
		rc = PTR_ERR(data->vdd);
		dev_err(&data->client->dev,
				"Regulator get failed vdd rc=%d\n", rc);
		return rc;
	}

	if (regulator_count_voltages(data->vdd) > 0) {
		rc = regulator_set_voltage(data->vdd, FT_VTG_MIN_UV,
								   FT_VTG_MAX_UV);
		if (rc) {
			dev_err(&data->client->dev,
					"Regulator set_vtg failed vdd rc=%d\n", rc);
			goto reg_vdd_put;
		}
	}

	data->vcc_i2c = regulator_get(&data->client->dev, "vcc_i2c");
	if (IS_ERR(data->vcc_i2c)) {
		rc = PTR_ERR(data->vcc_i2c);
		dev_err(&data->client->dev,
				"Regulator get failed vcc_i2c rc=%d\n", rc);
		goto reg_vdd_set_vtg;
	}

	if (regulator_count_voltages(data->vcc_i2c) > 0) {
		rc = regulator_set_voltage(data->vcc_i2c, FT_I2C_VTG_MIN_UV,
								   FT_I2C_VTG_MAX_UV);
		if (rc) {
			dev_err(&data->client->dev,
					"Regulator set_vtg failed vcc_i2c rc=%d\n", rc);
			goto reg_vcc_i2c_put;
		}
	}

	return 0;

reg_vcc_i2c_put:
	regulator_put(data->vcc_i2c);
reg_vdd_set_vtg:
	if (regulator_count_voltages(data->vdd) > 0)
		regulator_set_voltage(data->vdd, 0, FT_VTG_MAX_UV);
reg_vdd_put:
	regulator_put(data->vdd);
	return rc;

pwr_deinit:
	if (regulator_count_voltages(data->vdd) > 0)
		regulator_set_voltage(data->vdd, 0, FT_VTG_MAX_UV);

	regulator_put(data->vdd);

	if (regulator_count_voltages(data->vcc_i2c) > 0)
		regulator_set_voltage(data->vcc_i2c, 0, FT_I2C_VTG_MAX_UV);

	regulator_put(data->vcc_i2c);
	return 0;
}

<<<<<<< HEAD
static int ft5x06_ts_pinctrl_select(struct ft5x06_ts_data *ft5x06_data,
									bool on)
=======
static int ft5x06_ts_pinctrl_select(struct ft5x06_ts_data *ft5x06_data, bool on)
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
{
	struct pinctrl_state *pins_state;
	int ret;

	pins_state = on ? ft5x06_data->gpio_state_active
				 : ft5x06_data->gpio_state_suspend;
	if (!IS_ERR_OR_NULL(pins_state)) {
		ret = pinctrl_select_state(ft5x06_data->ts_pinctrl, pins_state);
		if (ret) {
			dev_err(&ft5x06_data->client->dev,
					"can not set %s pins\n",
					on ? "pmx_ts_active" : "pmx_ts_suspend");
			return ret;
		}
	} else {
		dev_err(&ft5x06_data->client->dev,
				"not a valid '%s' pinstate\n",
				on ? "pmx_ts_active" : "pmx_ts_suspend");
	}

	return 0;
}


#ifdef CONFIG_PM
static int ft5x06_ts_suspend(struct device *dev)
{
	struct ft5x06_ts_data *data = dev_get_drvdata(dev);
<<<<<<< HEAD
	char txbuf[2], i;
	int err;
=======
	int err;
	
	#ifdef CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE
	if(!dt2w_switch || in_phone_call){
	#endif
	char txbuf[2], i;
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207

	if (data->loading_fw) {
		dev_info(dev, "Firmware loading in process...\n");
		return 0;
	}
<<<<<<< HEAD

	if (data->suspended) {
		dev_info(dev, "Already in suspend state\n");
		return 0;
	}

	disable_irq(data->client->irq);

	/* release all touches */
	for (i = 0; i < data->pdata->num_max_touches; i++) {
		input_mt_slot(data->input_dev, i);
		input_mt_report_slot_state(data->input_dev, MT_TOOL_FINGER, 0);
	}
	input_mt_report_pointer_emulation(data->input_dev, false);
	input_sync(data->input_dev);

	if (gpio_is_valid(data->pdata->reset_gpio)) {
		txbuf[0] = FT_REG_PMODE;
		txbuf[1] = FT_PMODE_HIBERNATE;
		err = ft5x06_i2c_write(data->client, txbuf, sizeof(txbuf));

		msleep(data->pdata->hard_rst_dly);
	}

	if (data->pdata->power_on) {
		err = data->pdata->power_on(false);
		if (err) {
			dev_err(dev, "power off failed");
			goto pwr_off_fail;
		}
	} else {
		err = ft5x06_power_on(data, false);
		if (err) {
			dev_err(dev, "power off failed");
			goto pwr_off_fail;
		}
	}

	data->suspended = true;
=======
	
		if (data->suspended) {
			dev_info(dev, "Already in suspend state\n");
			return 0;
		}

		disable_irq(data->client->irq);

		/* release all touches */
		for (i = 0; i < data->pdata->num_max_touches; i++) {
			input_mt_slot(data->input_dev, i);
			input_mt_report_slot_state(data->input_dev, MT_TOOL_FINGER, 0);
		}
		input_mt_report_pointer_emulation(data->input_dev, false);
		input_sync(data->input_dev);

		if (gpio_is_valid(data->pdata->reset_gpio)) {
			txbuf[0] = FT_REG_PMODE;
			txbuf[1] = FT_PMODE_HIBERNATE;
			err = ft5x06_i2c_write(data->client, txbuf, sizeof(txbuf));
			msleep(data->pdata->hard_rst_dly);
		}
		
		if (data->pdata->power_on) {
			err = data->pdata->power_on(false);
			if (err) {
				dev_err(dev, "power off failed");
				goto pwr_off_fail;
			}
		} else {
			err = ft5x06_power_on(data, false);
 			if (err) {
 				dev_err(dev, "power off failed");
 				goto pwr_off_fail;
 			}
 		}
 
 		data->suspended = true;
 	#ifdef CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE
 	}
 	#endif
 	
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207

	return 0;


pwr_off_fail:
	if (gpio_is_valid(data->pdata->reset_gpio)) {
		gpio_set_value_cansleep(data->pdata->reset_gpio, 0);
		msleep(data->pdata->hard_rst_dly);
		gpio_set_value_cansleep(data->pdata->reset_gpio, 1);
	}
<<<<<<< HEAD
	enable_irq(data->client->irq);
=======
		msleep(data->pdata->soft_rst_dly);
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
	return err;

}

static int ft5x06_ts_resume(struct device *dev)
{
	struct ft5x06_ts_data *data = dev_get_drvdata(dev);
	int err;

<<<<<<< HEAD
	if (!data->suspended) {
		dev_dbg(dev, "Already in awake state\n");
		return 0;
	}


	if (data->pdata->power_on) {
		err = data->pdata->power_on(true);
		if (err) {
			dev_err(dev, "power on failed");
			return err;
		}
	} else {
		err = ft5x06_power_on(data, true);
		if (err) {
			dev_err(dev, "power on failed");
			return err;
		}
	}

	if (gpio_is_valid(data->pdata->reset_gpio)) {
		gpio_set_value_cansleep(data->pdata->reset_gpio, 0);
		msleep(data->pdata->hard_rst_dly);
		gpio_set_value_cansleep(data->pdata->reset_gpio, 1);
	}

	msleep(data->pdata->soft_rst_dly);
=======


		if (!data->suspended) {
 			dev_dbg(dev, "Already in awake state\n");
 			return 0;
		}
	
		if (data->pdata->power_on) {
 			err = data->pdata->power_on(true);
 			if (err) {
 				dev_err(dev, "power on failed");
 				return err;
 			}
 		} else {
 			err = ft5x06_power_on(data, true);
 			if (err) {
 				dev_err(dev, "power on failed");
 				return err;
 			}
 		}
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207

	enable_irq(data->client->irq);

#if CTP_CHARGER_DETECT
		batt_psy = power_supply_get_by_name("usb");
		if (!batt_psy)
			CTP_ERROR("tp resume battery supply not found\n");
		else {
			is_charger_plug = (u8)power_supply_get_battery_charge_state(batt_psy);

			CTP_DEBUG("is_charger_plug %d, prev %d", is_charger_plug, pre_charger_status);
			if (is_charger_plug) {
				ft5x0x_write_reg(update_client, 0x8B, 1);
			} else {
				ft5x0x_write_reg(update_client, 0x8B, 0);
			}
		}
		pre_charger_status = is_charger_plug;
#endif


	data->suspended = false;

	return 0;
}

static const struct dev_pm_ops ft5x06_ts_pm_ops = {
#if (!defined(CONFIG_FB) && !defined(CONFIG_HAS_EARLYSUSPEND))
	.suspend = ft5x06_ts_suspend,
	.resume = ft5x06_ts_resume,
#endif
};

#else
static int ft5x06_ts_suspend(struct device *dev)
{
	return 0;
}

static int ft5x06_ts_resume(struct device *dev)
{
	return 0;
}

#endif

#if defined(CONFIG_FB)

static void fb_notify_resume_work(struct work_struct *work)
{
	   struct ft5x06_ts_data *ft5x06_data =
			   container_of(work, struct ft5x06_ts_data, fb_notify_work);
	   ft5x06_ts_resume(&ft5x06_data->client->dev);
}
static int fb_notifier_callback(struct notifier_block *self,
								unsigned long event, void *data)
{
	struct fb_event *evdata = data;
	int *blank;
	struct ft5x06_ts_data *ft5x06_data =
			container_of(self, struct ft5x06_ts_data, fb_notif);

	if (evdata && evdata->data && event == FB_EVENT_BLANK &&
		ft5x06_data && ft5x06_data->client) {
		blank = evdata->data;
<<<<<<< HEAD
		if (*blank == FB_BLANK_UNBLANK
				|| *blank == FB_BLANK_NORMAL
				|| *blank == FB_BLANK_VSYNC_SUSPEND)
		   schedule_work(&ft5x06_data->fb_notify_work);
		 else if (*blank == FB_BLANK_POWERDOWN) {
			flush_work(&ft5x06_data->fb_notify_work);
			ft5x06_ts_suspend(&ft5x06_data->client->dev);
=======
		if (*blank == FB_BLANK_UNBLANK){
			
		   schedule_work(&ft5x06_data->fb_notify_work);
			#ifdef CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE
			dt2w_scr_suspended = false;
			#endif
					}
		 else if (*blank == FB_BLANK_POWERDOWN) {
			flush_work(&ft5x06_data->fb_notify_work);
			ft5x06_ts_suspend(&ft5x06_data->client->dev);
			#ifdef CONFIG_TOUCHSCREEN_DOUBLETAP2WAKE
			dt2w_scr_suspended = true;
			#endif
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
		}
	}

	return 0;
}
#elif defined(CONFIG_HAS_EARLYSUSPEND)
static void ft5x06_ts_early_suspend(struct early_suspend *handler)
{
	struct ft5x06_ts_data *data = container_of(handler,
								  struct ft5x06_ts_data,
								  early_suspend);

	ft5x06_ts_suspend(&data->client->dev);
}

static void ft5x06_ts_late_resume(struct early_suspend *handler)
{
	struct ft5x06_ts_data *data = container_of(handler,
								  struct ft5x06_ts_data,
								  early_suspend);

	ft5x06_ts_resume(&data->client->dev);
}
#endif

<<<<<<< HEAD
#ifdef CONFIG_OF
static int ft5x06_get_dt_coords(struct device *dev, char *name,
								struct ft5x06_ts_platform_data *pdata)
{
	u32 coords[FT_COORDS_ARR_SIZE];
	struct property *prop;
	struct device_node *np = dev->of_node;
	int coords_size, rc;

	prop = of_find_property(np, name, NULL);
	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;

	coords_size = prop->length / sizeof(u32);
	if (coords_size != FT_COORDS_ARR_SIZE) {
		dev_err(dev, "invalid %s\n", name);
		return -EINVAL;
	}

	rc = of_property_read_u32_array(np, name, coords, coords_size);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read %s\n", name);
		return rc;
	}

	if (!strcmp(name, "ftech,panel-coords")) {
		pdata->panel_minx = coords[0];
		pdata->panel_miny = coords[1];
		pdata->panel_maxx = coords[2];
		pdata->panel_maxy = coords[3];
	} else if (!strcmp(name, "ftech,display-coords")) {
		pdata->x_min = coords[0];
		pdata->y_min = coords[1];
		pdata->x_max = coords[2];
		pdata->y_max = coords[3];
	} else {
		dev_err(dev, "unsupported property %s\n", name);
		return -EINVAL;
	}

	return 0;
}

static int ft5x06_parse_dt(struct device *dev,
						   struct ft5x06_ts_platform_data *pdata)
{
	int rc;
	struct device_node *np = dev->of_node;
	struct property *prop;
	u32 temp_val, num_buttons;
	u32 button_map[MAX_BUTTONS];

	pdata->name = "ftech";
	rc = of_property_read_string(np, "ftech,name", &pdata->name);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read name\n");
		return rc;
	}

	rc = ft5x06_get_dt_coords(dev, "ftech,panel-coords", pdata);
	if (rc && (rc != -EINVAL))
		return rc;

	rc = ft5x06_get_dt_coords(dev, "ftech,display-coords", pdata);
	if (rc)
		return rc;


	pdata->i2c_pull_up = of_property_read_bool(np, "ftech,i2c-pull-up");

	pdata->no_force_update = of_property_read_bool(np,"ftech,no-force-update");
	/* reset, irq gpio info */
	pdata->reset_gpio = of_get_named_gpio_flags(np, "ftech,reset-gpio",
						0, &pdata->reset_gpio_flags);
	if (pdata->reset_gpio < 0)
		return pdata->reset_gpio;

	pdata->irq_gpio = of_get_named_gpio_flags(np, "ftech,irq-gpio", 0, &pdata->irq_gpio_flags);
	if (pdata->irq_gpio < 0)
		return pdata->irq_gpio;

	pdata->fw_name = "ft_fw.bin";
	rc = of_property_read_string(np, "ftech,fw-name", &pdata->fw_name);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw name\n");
		return rc;
	}

	rc = of_property_read_u32(np, "ftech,group-id", &temp_val);
	if (!rc)
		pdata->group_id = temp_val;
	else
		return rc;

	rc = of_property_read_u32(np, "ftech,hard-reset-delay-ms",
							  &temp_val);
	if (!rc)
		pdata->hard_rst_dly = temp_val;
	else
		return rc;

	rc = of_property_read_u32(np, "ftech,soft-reset-delay-ms",
							  &temp_val);
	if (!rc)
		pdata->soft_rst_dly = temp_val;
	else
		return rc;

	rc = of_property_read_u32(np, "ftech,num-max-touches", &temp_val);
	if (!rc)
	pdata->num_max_touches = temp_val;
	else
		return rc;

	rc = of_property_read_u32(np, "ftech,fw-delay-aa-ms", &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw delay aa\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.delay_aa =  temp_val;

	rc = of_property_read_u32(np, "ftech,fw-delay-55-ms", &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw delay 55\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.delay_55 =  temp_val;

	rc = of_property_read_u32(np, "ftech,fw-upgrade-id1", &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw upgrade id1\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.upgrade_id_1 =  temp_val;

	rc = of_property_read_u32(np, "ftech,fw-upgrade-id2", &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw upgrade id2\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.upgrade_id_2 =  temp_val;

	rc = of_property_read_u32(np, "ftech,fw-delay-readid-ms",
							  &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw delay read id\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.delay_readid =  temp_val;

	rc = of_property_read_u32(np, "ftech,fw-delay-era-flsh-ms",
							  &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw delay erase flash\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.delay_erase_flash =  temp_val;

	pdata->info.auto_cal = of_property_read_bool(np,
						   "ftech,fw-auto-cal");

	pdata->fw_vkey_support = of_property_read_bool(np,
							 "ftech,fw-vkey-support");

	pdata->ignore_id_check = of_property_read_bool(np,
							 "ftech,ignore-id-check");

	rc = of_property_read_u32(np, "ftech,family-id", &temp_val);
	if (!rc)
		pdata->family_id = temp_val;
	else
		return rc;

	prop = of_find_property(np, "ftech,button-map", NULL);
	if (prop) {
		num_buttons = prop->length / sizeof(temp_val);
		if (num_buttons > MAX_BUTTONS)
			return -EINVAL;

		rc = of_property_read_u32_array(np,
										"ftech,button-map", button_map,
=======

























































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































#ifdef CONFIG_OF
static int ft5x06_get_dt_coords(struct device *dev, char *name,
								struct ft5x06_ts_platform_data *pdata)
{
	u32 coords[FT_COORDS_ARR_SIZE];
	struct property *prop;
	struct device_node *np = dev->of_node;
	int coords_size, rc;

	prop = of_find_property(np, name, NULL);
	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;

	coords_size = prop->length / sizeof(u32);
	if (coords_size != FT_COORDS_ARR_SIZE) {
		dev_err(dev, "invalid %s\n", name);
		return -EINVAL;
	}

	rc = of_property_read_u32_array(np, name, coords, coords_size);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read %s\n", name);
		return rc;
	}

	if (!strcmp(name, "ftech,panel-coords")) {
		pdata->panel_minx = coords[0];
		pdata->panel_miny = coords[1];
		pdata->panel_maxx = coords[2];
		pdata->panel_maxy = coords[3];
	} else if (!strcmp(name, "ftech,display-coords")) {
		pdata->x_min = coords[0];
		pdata->y_min = coords[1];
		pdata->x_max = coords[2];
		pdata->y_max = coords[3];
	} else {
		dev_err(dev, "unsupported property %s\n", name);
		return -EINVAL;
	}

	return 0;
}

static int ft5x06_parse_dt(struct device *dev,
						   struct ft5x06_ts_platform_data *pdata)
{
	int rc;
	struct device_node *np = dev->of_node;
	struct property *prop;
	u32 temp_val, num_buttons;
	u32 button_map[MAX_BUTTONS];

	pdata->name = "ftech";
	rc = of_property_read_string(np, "ftech,name", &pdata->name);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read name\n");
		return rc;
	}

	rc = ft5x06_get_dt_coords(dev, "ftech,panel-coords", pdata);
	if (rc && (rc != -EINVAL))
		return rc;

	rc = ft5x06_get_dt_coords(dev, "ftech,display-coords", pdata);
	if (rc)
		return rc;


	pdata->i2c_pull_up = of_property_read_bool(np, "ftech,i2c-pull-up");

	pdata->no_force_update = of_property_read_bool(np,"ftech,no-force-update");
	/* reset, irq gpio info */
	pdata->reset_gpio = of_get_named_gpio_flags(np, "ftech,reset-gpio",
						0, &pdata->reset_gpio_flags);
	if (pdata->reset_gpio < 0)
		return pdata->reset_gpio;

	pdata->irq_gpio = of_get_named_gpio_flags(np, "ftech,irq-gpio", 0, &pdata->irq_gpio_flags);
	if (pdata->irq_gpio < 0)
		return pdata->irq_gpio;

	pdata->fw_name = "ft_fw.bin";
	rc = of_property_read_string(np, "ftech,fw-name", &pdata->fw_name);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw name\n");
		return rc;
	}

	rc = of_property_read_u32(np, "ftech,group-id", &temp_val);
	if (!rc)
		pdata->group_id = temp_val;
	else
		return rc;

	rc = of_property_read_u32(np, "ftech,hard-reset-delay-ms",
							  &temp_val);
	if (!rc)
		pdata->hard_rst_dly = temp_val;
	else
		return rc;

	rc = of_property_read_u32(np, "ftech,soft-reset-delay-ms",
							  &temp_val);
	if (!rc)
		pdata->soft_rst_dly = temp_val;
	else
		return rc;

	rc = of_property_read_u32(np, "ftech,num-max-touches", &temp_val);
	if (!rc)
	pdata->num_max_touches = temp_val;
	else
		return rc;

	rc = of_property_read_u32(np, "ftech,fw-delay-aa-ms", &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw delay aa\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.delay_aa =  temp_val;

	rc = of_property_read_u32(np, "ftech,fw-delay-55-ms", &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw delay 55\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.delay_55 =  temp_val;

	rc = of_property_read_u32(np, "ftech,fw-upgrade-id1", &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw upgrade id1\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.upgrade_id_1 =  temp_val;

	rc = of_property_read_u32(np, "ftech,fw-upgrade-id2", &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw upgrade id2\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.upgrade_id_2 =  temp_val;

	rc = of_property_read_u32(np, "ftech,fw-delay-readid-ms",
							  &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw delay read id\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.delay_readid =  temp_val;

	rc = of_property_read_u32(np, "ftech,fw-delay-era-flsh-ms",
							  &temp_val);
	if (rc && (rc != -EINVAL)) {
		dev_err(dev, "Unable to read fw delay erase flash\n");
		return rc;
	} else if (rc != -EINVAL)
		pdata->info.delay_erase_flash =  temp_val;

	pdata->info.auto_cal = of_property_read_bool(np,
						   "ftech,fw-auto-cal");

	pdata->fw_vkey_support = of_property_read_bool(np,
							 "ftech,fw-vkey-support");

	pdata->ignore_id_check = of_property_read_bool(np,
							 "ftech,ignore-id-check");

	rc = of_property_read_u32(np, "ftech,family-id", &temp_val);
	if (!rc)
		pdata->family_id = temp_val;
	else
		return rc;

	prop = of_find_property(np, "ftech,button-map", NULL);
	if (prop) {
		num_buttons = prop->length / sizeof(temp_val);
		if (num_buttons > MAX_BUTTONS)
			return -EINVAL;

		rc = of_property_read_u32_array(np,
										"ftech,button-map", button_map,
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
										num_buttons);
		if (rc) {
			dev_err(dev, "Unable to read key codes\n");
			return rc;
		}
	}

	return 0;
}
#else
static int ft5x06_parse_dt(struct device *dev,
						   struct ft5x06_ts_platform_data *pdata)
{
	return -ENODEV;
}
#endif

<<<<<<< HEAD
=======












































































>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
static int ft5x06_ts_probe(struct i2c_client *client,
						   const struct i2c_device_id *id)
{
	struct ft5x06_ts_platform_data *pdata;
	struct ft5x06_ts_data *data;
	struct input_dev *input_dev;
	struct dentry *temp;
	u8 reg_value;
	u8 reg_addr;
	int err;
	int len;
	u8 ic_name;
	temp = NULL;
	update_client = client;

	if (client->dev.of_node) {
		pdata = devm_kzalloc(&client->dev,
							 sizeof(struct ft5x06_ts_platform_data), GFP_KERNEL);
		if (!pdata) {
			dev_err(&client->dev, "Failed to allocate memory\n");
			return -ENOMEM;
		}

		err = ft5x06_parse_dt(&client->dev, pdata);
		if (err) {
			dev_err(&client->dev, "DT parsing failed\n");
			return err;
		}
	} else
		pdata = client->dev.platform_data;

	if (!pdata) {
		dev_err(&client->dev, "Invalid pdata\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "I2C not supported\n");
		return -ENODEV;
	}

	data = devm_kzalloc(&client->dev,
						sizeof(struct ft5x06_ts_data), GFP_KERNEL);
	if (!data) {
		dev_err(&client->dev, "Not enough memory\n");
		return -ENOMEM;
	}

	if (pdata->fw_name) {
		len = strlen(pdata->fw_name);
		if (len > FT_FW_NAME_MAX_LEN - 1) {
			dev_err(&client->dev, "Invalid firmware name\n");
			return -EINVAL;
		}

		strlcpy(data->fw_name, pdata->fw_name, len + 1);
	}

	data->tch_data_len = FT_TCH_LEN(pdata->num_max_touches);
	data->tch_data = devm_kzalloc(&client->dev,
								  data->tch_data_len, GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	input_dev = input_allocate_device();
	if (!input_dev)
		return -ENOMEM;

	data->input_dev = input_dev;
	data->client = client;
	data->pdata = pdata;

	input_dev->name = "ft5x06_720p";
	input_dev->id.bustype = BUS_I2C;
	input_dev->dev.parent = &client->dev;

	input_set_drvdata(input_dev, data);
	i2c_set_clientdata(client, data);

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(INPUT_PROP_DIRECT, input_dev->propbit);

	input_mt_init_slots(input_dev, pdata->num_max_touches, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_X, pdata->x_min,
						 pdata->x_max, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, pdata->y_min,
						 pdata->y_max, 0, 0);

	err = input_register_device(input_dev);
	if (err) {
		dev_err(&client->dev, "Input device registration failed\n");
		goto free_inputdev;
	}

	if (pdata->power_init) {
		err = pdata->power_init(true);
		if (err) {
			dev_err(&client->dev, "power init failed");
			goto unreg_inputdev;
		}
	} else {
		err = ft5x06_power_init(data, true);
		if (err) {
			dev_err(&client->dev, "power init failed");
			goto unreg_inputdev;
		}
	}

	if (pdata->power_on) {
		err = pdata->power_on(true);
		if (err) {
			dev_err(&client->dev, "power on failed");
			goto pwr_deinit;
		}
	} else {
		err = ft5x06_power_on(data, true);
		if (err) {
			dev_err(&client->dev, "power on failed");
			goto pwr_deinit;
		}
	}


	if (gpio_is_valid(pdata->irq_gpio)) {
		err = gpio_request(pdata->irq_gpio, "ft5x06_irq_gpio");
		if (err) {
			dev_err(&client->dev, "irq gpio request failed");
			goto pwr_off;
		}
		err = gpio_direction_input(pdata->irq_gpio);
		if (err) {
			dev_err(&client->dev,
					"set_direction for irq gpio failed\n");
			goto free_irq_gpio;
		}
	}

	if (gpio_is_valid(pdata->reset_gpio)) {
		err = gpio_request(pdata->reset_gpio, "ft5x06_reset_gpio");
		if (err)
			goto free_irq_gpio;

		err = gpio_direction_output(pdata->reset_gpio, 0);
		if (err) {
			dev_err(&client->dev,
					"set_direction for reset gpio failed\n");
			goto free_reset_gpio;
		}
		msleep(data->pdata->hard_rst_dly);
		gpio_set_value_cansleep(data->pdata->reset_gpio, 1);
	}

	/* make sure CTP already finish startup process */
	msleep(data->pdata->soft_rst_dly);

	/* check the controller id */
	reg_addr = FT_REG_ID;
	do { //Search for the correct register.
		err = ft5x06_i2c_read(client, &reg_addr, 1, &reg_value, 1);
		if (err < 0) {
			dev_err(&client->dev, "version read failed");
			//goto free_reset_gpio;
		}
		if(reg_value!=0x14){
		 	client->addr = client->addr + 0x1;
		}else{
			dev_info(&client->dev, "Touchpanel Register found: 0x%x\n",client->addr);
			break;
		}
	}while(reg_value!=0x14);//We expect it to be 0x14 for FT5336

	ic_name = reg_value;

	dev_info(&client->dev, "Device ID = 0x%x\n", reg_value);

	if ((pdata->family_id != reg_value) && (!pdata->ignore_id_check)) {
		dev_err(&client->dev, "%s:Unsupported controller\n", __func__);
		goto free_reset_gpio;
	}

	data->family_id = pdata->family_id;

	err = request_threaded_irq(client->irq, NULL,
							   ft5x06_ts_interrupt,
							   pdata->irq_gpio_flags | IRQF_ONESHOT,
							   client->dev.driver->name, data);
	if (err) {
		dev_err(&client->dev, "request irq failed\n");
		goto free_reset_gpio;
	}

	disable_irq(data->client->irq);



<<<<<<< HEAD
=======














>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207
	data->ts_info = devm_kzalloc(&client->dev,
								 FT_INFO_MAX_LEN, GFP_KERNEL);
	if (!data->ts_info) {
		dev_err(&client->dev, "Not enough memory\n");
		goto free_irq_gpio;
	}

	/*get some register information */
	reg_addr = FT_REG_POINT_RATE;
	ft5x06_i2c_read(client, &reg_addr, 1, &reg_value, 1);
	if (err < 0)
		dev_err(&client->dev, "report rate read failed");

	dev_info(&client->dev, "report rate = %dHz\n", reg_value * 10);

	reg_addr = FT_REG_THGROUP;
	err = ft5x06_i2c_read(client, &reg_addr, 1, &reg_value, 1);
	if (err < 0)
		dev_err(&client->dev, "threshold read failed");

	dev_dbg(&client->dev, "touch threshold = %d\n", reg_value * 4);

	ft5x06_update_fw_vendor_id(data);

	FT_STORE_TS_INFO(data->ts_info, data->family_id, data->pdata->name,
					 data->pdata->num_max_touches, data->pdata->group_id,
					 data->pdata->fw_vkey_support ? "yes" : "no",
					 data->pdata->fw_name, data->fw_ver[0],
					 data->fw_ver[1], data->fw_ver[2]);

#if defined(CONFIG_FB)
	INIT_WORK(&data->fb_notify_work, fb_notify_resume_work);
	data->fb_notif.notifier_call = fb_notifier_callback;

	err = fb_register_client(&data->fb_notif);

	if (err)
		dev_err(&client->dev, "Unable to register fb_notifier: %d\n",
				err);
#elif defined(CONFIG_HAS_EARLYSUSPEND)
	data->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN +
								FT_SUSPEND_LEVEL;
	data->early_suspend.suspend = ft5x06_ts_early_suspend;
	data->early_suspend.resume = ft5x06_ts_late_resume;
	register_early_suspend(&data->early_suspend);
#endif

#if CTP_CHARGER_DETECT
	batt_psy = power_supply_get_by_name("usb");
	if (!batt_psy)
		CTP_DEBUG("tp battery supply not found\n");
#endif

	enable_irq(data->client->irq);

	return 0;


free_reset_gpio:
   if (gpio_is_valid(pdata->reset_gpio))
		gpio_free(pdata->reset_gpio);
	if (data->ts_pinctrl) {
		err = ft5x06_ts_pinctrl_select(data, false);
		if (err < 0)
			CTP_ERROR("Cannot get idle pinctrl state\n");
	}
free_irq_gpio:
	if (gpio_is_valid(pdata->irq_gpio))
		gpio_free(pdata->irq_gpio);
	if (data->ts_pinctrl) {
		err = ft5x06_ts_pinctrl_select(data, false);
		if (err < 0)
			CTP_ERROR("Cannot get idle pinctrl state\n");
	}
pwr_off:
	if (pdata->power_on)
		pdata->power_on(false);
	else
		ft5x06_power_on(data, false);
pwr_deinit:
	if (pdata->power_init)
		pdata->power_init(false);
	else
		ft5x06_power_init(data, false);
unreg_inputdev:
	input_unregister_device(input_dev);
	input_dev = NULL;
free_inputdev:
	input_free_device(input_dev);
	return err;
}

static int ft5x06_ts_remove(struct i2c_client *client)
{
	struct ft5x06_ts_data *data = i2c_get_clientdata(client);
	int retval;

#if defined(CONFIG_FB)
	if (fb_unregister_client(&data->fb_notif))
		dev_err(&client->dev, "Error occurred while unregistering fb_notifier.\n");
#elif defined(CONFIG_HAS_EARLYSUSPEND)
	unregister_early_suspend(&data->early_suspend);
#endif
	free_irq(client->irq, data);

	if (gpio_is_valid(data->pdata->reset_gpio))
		gpio_free(data->pdata->reset_gpio);

	if (gpio_is_valid(data->pdata->irq_gpio))
		gpio_free(data->pdata->irq_gpio);

	if (data->ts_pinctrl) {
		retval = ft5x06_ts_pinctrl_select(data, false);
		if (retval < 0)
			CTP_ERROR("Cannot get idle pinctrl state\n");
	}

	if (data->pdata->power_on)
		data->pdata->power_on(false);
	else
		ft5x06_power_on(data, false);

	if (data->pdata->power_init)
		data->pdata->power_init(false);
	else
		ft5x06_power_init(data, false);

	input_unregister_device(data->input_dev);

	return 0;
}

static const struct i2c_device_id ft5x06_ts_id[] = {
	{"ft5x06_720p", 0},
	{},
};

MODULE_DEVICE_TABLE(i2c, ft5x06_ts_id);

#ifdef CONFIG_OF
static struct of_device_id ft5x06_match_table[] = {
	{.compatible = "focaltech,5336",},
	{},
};
#else
#define ft5x06_match_table NULL
#endif

static struct i2c_driver ft5x06_ts_driver = {
	.probe = ft5x06_ts_probe,
	.remove = ft5x06_ts_remove,
	.driver = {
		.name = "ft5x06_720p",
		.owner = THIS_MODULE,
		.of_match_table = ft5x06_match_table,
#ifdef CONFIG_PM
		.pm = &ft5x06_ts_pm_ops,
#endif
	},
	.id_table = ft5x06_ts_id,
};

static int __init ft5x06_ts_init(void)
{
	return i2c_add_driver(&ft5x06_ts_driver);
}
module_init(ft5x06_ts_init);

static void __exit ft5x06_ts_exit(void)
{
	i2c_del_driver(&ft5x06_ts_driver);
}
module_exit(ft5x06_ts_exit);

MODULE_DESCRIPTION("FocalTech ft5x06 TouchScreen driver");
<<<<<<< HEAD
MODULE_LICENSE("GPL v2");
=======
MODULE_LICENSE("GPL v2");
>>>>>>> 5a6f4fe3ec2e1c1fd85bf1a97671dee8cf8e2207

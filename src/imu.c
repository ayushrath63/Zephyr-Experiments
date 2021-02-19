#include "imu.h"

const struct device *lsm6dsl_dev;

static void imu_trigger_handler(struct device *dev, struct sensor_trigger *trig)
{
    bool status = true;
    status &= sensor_sample_fetch_chan(dev, SENSOR_CHAN_ACCEL_XYZ);
    status &= sensor_sample_fetch_chan(dev, SENSOR_CHAN_GYRO_XYZ);
    if(status != 0)
    {
        printk("LSM6DSL sample capture failed!\n");
    }

    return;
}

bool imu_init()
{
	lsm6dsl_dev = device_get_binding(DT_LABEL(DT_INST(0, st_lsm6dsl)));

	if (lsm6dsl_dev == NULL) {
		printk("Could not get LSM6DSL device\n");
		return false;
	}

    struct sensor_trigger trig = 
    {
        .type = SENSOR_TRIG_DATA_READY,
        .chan = SENSOR_CHAN_ACCEL_XYZ
    };

    if (sensor_trigger_set(lsm6dsl_dev, &trig, (sensor_trigger_handler_t)imu_trigger_handler) != 0) {
		printk("Could not set sensor type and channel\n");
		return false;
	}

    return true;
}

inline double imu_fetch_gyroX()
{
    static struct sensor_value gyro_x;
    bool status = sensor_channel_get(lsm6dsl_dev, SENSOR_CHAN_GYRO_X, &gyro_x);
    if(status != 0)
    {
        printk("LSM6DSL Gyro X sample read failed!\n");
    }
    return sensor_value_to_double(&gyro_x);
}

inline double imu_fetch_gyroY()
{
    static struct sensor_value gyro_y;
    bool status = sensor_channel_get(lsm6dsl_dev, SENSOR_CHAN_GYRO_Y, &gyro_y);
    if(status != 0)
    {
        printk("LSM6DSL Gyro Y sample read failed!\n");
    }
    return sensor_value_to_double(&gyro_y);
}

inline double imu_fetch_gyroZ()
{
    static struct sensor_value gyro_z;
    bool status = sensor_channel_get(lsm6dsl_dev, SENSOR_CHAN_GYRO_Z, &gyro_z);
    if(status != 0)
    {
        printk("LSM6DSL Gyro Z sample read failed!\n");
    }
    return sensor_value_to_double(&gyro_z);
}

void imu_fetch_gyroXYZ(double *gyroX, double *gyroY, double *gyroZ)
{
    *gyroX = imu_fetch_gyroX();
    *gyroY = imu_fetch_gyroY();
    *gyroZ = imu_fetch_gyroZ();
}

double imu_fetch_accelX()
{
    static struct sensor_value accel_x;
    bool status = sensor_channel_get(lsm6dsl_dev, SENSOR_CHAN_ACCEL_X, &accel_x);
    if(status != 0)
    {
        printk("LSM6DSL Accel X sample read failed!\n");
    }
    return sensor_value_to_double(&accel_x);
}

double imu_fetch_accelY()
{
    static struct sensor_value accel_y;
    bool status = sensor_channel_get(lsm6dsl_dev, SENSOR_CHAN_ACCEL_Y, &accel_y);
    if(status != 0)
    {
        printk("LSM6DSL Accel Y sample read failed!\n");
    }
    return sensor_value_to_double(&accel_y);
}

double imu_fetch_accelZ()
{
    static struct sensor_value accel_z;
    bool status = sensor_channel_get(lsm6dsl_dev, SENSOR_CHAN_ACCEL_Z, &accel_z);
    if(status != 0)
    {
        printk("LSM6DSL Accel Z sample read failed!\n");
    }
    return sensor_value_to_double(&accel_z);
}

void imu_fetch_accelXYZ(double *accelX, double *accelY, double *accelZ)
{
    *accelX = imu_fetch_accelX();
    *accelY = imu_fetch_accelY();
    *accelZ = imu_fetch_accelZ();
}
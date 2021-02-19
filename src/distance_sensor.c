#include "distance_sensor.h"

const struct device *dist_sensor;
struct sensor_value dist_sensor_value;

bool dist_sensor_init()
{

    dist_sensor = device_get_binding(DT_LABEL(DT_INST(0, st_vl53l0x)));
    if (!dist_sensor)
    {
        printk("Could not get VL53L0X device\n");
        return false;
    }
    return true;
}

void sample_dist_sensor()
{
    while(1)
    {
        bool status = sensor_sample_fetch(dist_sensor);
        if(status != 0)
        {
            printk("VL53L0X sample capture failed!\n");
        }
        k_msleep(1);
    }
}

bool fetch_dist_sensor_prox()
{
    bool status = sensor_channel_get(dist_sensor, SENSOR_CHAN_PROX, &dist_sensor_value);
    if (status != 0)
    {
        printk("VL53L0X sample read failed!\n");
    }
    return dist_sensor_value.val1;
}

double fetch_dist_sensor_val()
{
    bool status = sensor_channel_get(dist_sensor, SENSOR_CHAN_DISTANCE, &dist_sensor_value);
    if (status != 0)
    {
        printk("VL53L0X sample read failed!\n");
    }
    return sensor_value_to_double(&dist_sensor_value);
}
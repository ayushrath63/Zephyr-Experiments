#pragma once

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <sys/printk.h>

bool dist_sensor_init();

void sample_dist_sensor();
bool fetch_dist_sensor_prox();
double fetch_dist_sensor_val();
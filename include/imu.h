#pragma once

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <sys/printk.h>

bool imu_init();

double imu_fetch_gyroX();
double imu_fetch_gyroY();
double imu_fetch_gyroZ();
void imu_fetch_gyroXYZ(double *gyroX, double *gyroY, double *gyroZ);

double imu_fetch_accelX();
double imu_fetch_accelY();
double imu_fetch_accelZ();
void imu_fetch_accelXYZ(double *accelX, double *accelY, double *accelZ);
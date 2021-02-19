/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <drivers/uart.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <sys/printk.h>
#include "led.h"
#include "distance_sensor.h"
#include "imu.h"

#include <pb_decode.h>
#include "serial_pb/simple.pb.h"


/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000
#define STACKSIZE 500
#define LED_PRIORITY 5
#define DIST_SENSOR_PRIORITY 4
#define IMU_PRIORITY 4

K_THREAD_DEFINE(blink0_id, STACKSIZE, blink0, NULL, NULL, NULL,
	LED_PRIORITY, 0, 0);
K_THREAD_DEFINE(blink1_id, STACKSIZE, blink1, NULL, NULL, NULL,
	LED_PRIORITY, 0, 0);
K_THREAD_DEFINE(dist_sensor_sample_id, STACKSIZE, sample_dist_sensor, NULL, NULL, NULL,
	DIST_SENSOR_PRIORITY, 0, 0);

#define UART1_NODE DT_NODELABEL(usart1)
#if DT_NODE_HAS_STATUS(UART1_NODE, okay)
#define UART1	DT_LABEL(UART1_NODE)
#endif
void main(void)
{
	led_init();
	dist_sensor_init();
	imu_init();

	bool proximity_flag;
	double dist_meas;

	double accel_x, accel_y, accel_z;
	double gyro_x, gyro_y, gyro_z;

	SimpleMessage message = SimpleMessage_init_zero;

	/* Fill in the lucky number */
	message.lucky_number = 13;
	message.lucky_number2 = 11;

	const struct device *uart_dev = device_get_binding(UART1);
	uart_poll_out(uart_dev, &message);

	while (1)
	{
		/* vl53l0x proximity & distance */
		proximity_flag = fetch_dist_sensor_prox();
		dist_meas = fetch_dist_sensor_val();
		// printk("vl53l0x:\n");
		// printk("\tproximity_flag = %d\n", proximity_flag);
		// printf("\tdistance = %.3fm\n", dist_meas);

		/* lsm6dsl accel */
		imu_fetch_accelXYZ(&accel_x, &accel_y, &accel_z);
		// printf("lsm6dsl accel:\n\tx: %f ms/2\n\ty: %f ms/2\n\tz: %f ms/2\n",
		// 					  accel_x,
		// 					  accel_y,
		// 					  accel_z);

		/* lsm6dsl gyro */
		imu_fetch_gyroXYZ(&gyro_x, &gyro_y, &gyro_z);
		// printf("lsm6dsl gyro:\n\tx: %f dps\n\ty: %f dps\n\tz: %f dps\n",
		// 					   gyro_x,
		// 					   gyro_y,
		// 					   gyro_z);

		// printk("\n");

		k_msleep(SLEEP_TIME_MS);
	}
}

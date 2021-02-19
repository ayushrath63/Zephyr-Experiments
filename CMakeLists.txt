# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
set(NO_BUILD_TYPE_WARNING 1)

set(BOARD_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(BOARD disco_l475_iot1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)

include(src/serial_pb/serial_pb.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/nanopb/)
add_dependencies(app serial_pb)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_sources(app PRIVATE src/led.c)
target_sources(app PRIVATE src/distance_sensor.c)
target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/imu.c)
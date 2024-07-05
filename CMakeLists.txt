# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

cmake_path(SET ZephyrBase $ENV{ZEPHYR_BASE})

set(SMALLVM_PATH ../modules/microblocks/vm)
set(ARDUINO_ZEPHYR_PATH ${ZephyrBase}/../modules/lib/Arduino-Zephyr-API)
set(EXTRA_DTC_OVERLAY_FILE ${ARDUINO_ZEPHYR_PATH}/variants/${BOARD}/${BOARD}.overlay)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)

target_include_directories(app PRIVATE ${SMALLVM_PATH})

file(GLOB VM ${SMALLVM_PATH}/*.c ${SMALLVM_PATH}/*.cpp)
target_sources(app PRIVATE ${VM})
target_sources(app PRIVATE ${ARDUINO_ZEPHYR_PATH}/cores/arduino/api/Stream.cpp)

target_sources_ifdef(CONFIG_LOG app PRIVATE src/log_backend.c)

target_sources(app PRIVATE src/main.c)

zephyr_compile_options(-Wno-unused-variable -Wno-comment)

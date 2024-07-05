// SPDX-License-Identifier: Apache-2.0
/*
 * Copyright (c) 2024 Ayush Singh <ayush@beagleboard.org>
 */

#include "interp.h"
#include <zephyr/logging/log_backend.h>
#include <zephyr/logging/log_backend_std.h>
#include <zephyr/logging/log_output.h>

#define BUFFER_LEN 100

static uint8_t microblocks_output_buffer[BUFFER_LEN];

static int microblocks_out(uint8_t *data, size_t length, void *ctx) {
  ARG_UNUSED(ctx);

  data[length] = 0;
  outputString(data);

  return length;
}

LOG_OUTPUT_DEFINE(microblocks_log_output, microblocks_out,
                  microblocks_output_buffer, BUFFER_LEN - 1);

static void microblocks_backend_process(const struct log_backend *const backend,
                                        union log_msg_generic *msg) {
  ARG_UNUSED(backend);

  // uint32_t flags = log_backend_std_get_flags();
	uint32_t flags = LOG_OUTPUT_FLAG_LEVEL;

  log_output_msg_process(&microblocks_log_output, &msg->log, flags);
}

static void microblocks_backend_dropped(const struct log_backend *const backend,
                                        uint32_t cnt) {
  ARG_UNUSED(backend);

  log_backend_std_dropped(&microblocks_log_output, cnt);
}

static void microblocks_backend_panic(const struct log_backend *const backend) {
  ARG_UNUSED(backend);

  log_backend_std_panic(&microblocks_log_output);
}

static int
microblocks_backend_is_ready(const struct log_backend *const backend) {
  ARG_UNUSED(backend);

  if (ideConnected()) {
    return 0;
  } else {
    return -EBUSY;
  }
}

const struct log_backend_api microblocks_log_backend_api = {
    .process = microblocks_backend_process,
    .dropped = microblocks_backend_dropped,
    .panic = microblocks_backend_panic,
    .is_ready = microblocks_backend_is_ready};

LOG_BACKEND_DEFINE(microblocks_log_backend, microblocks_log_backend_api, true);

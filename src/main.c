/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

// Copyright 2018 John Maloney, Bernat Romagosa, and Jens Mönig

#include "interp.h"
#include "mem.h"
#include "persist.h"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(smallvm, CONFIG_SMALLVM_LOG_LEVEL);

int main(void) {
  hardwareInit();
  memInit();
  primsInit();
  outputString((char *)"Welcome to MicroBlocks!");
  restoreScripts();
  startAll();

  vmLoop();

  return 0;
}

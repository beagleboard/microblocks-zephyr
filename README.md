# MicroBlocks on Zephyr

This repository is aimed to build [MicroBlocks](https://microblocks.fun/) for Zephyr boards. While it is only being used for BeagleConnect Freedom for now, it can be easily exteneded to support other boards.

# Setup

If this is your first time using zephyr, [Install Zephyr SDK](https://docs.zephyrproject.org/latest/develop/getting_started/index.html#install-the-zephyr-sdk) before following the steps below.

1. Create a workspace folder:

```shell
mkdir microblocks-workspace
cd microblocks-workspace
```

2. Setup virtualenv

```shell
python -m venv .venv
source .venv/bin/activate
pip install west cc1352-flasher
```

3. Setup Zephyr app:

```shell
west init -m https://github.com/beagleboard/microblocks-zephyr.git --mf west_pilot.yml .
west update
```

4. Setup Arduino module

```shell
ln -srf modules/lib/ArduinoCore-API/api modules/lib/Arduino-Zephyr-API/cores/arduino/.
```

5. Install python deps

```shell
west packages pip --install
```

# Build

```shell
west build -b beagleconnect_freedom microblocks-zephyr.git -p
```

# Flash

```shell
west flash
```

# Helpful Links
- [MicroBlocks](https://microblocks.fun/)
- [Arduino Core API module for Zephyr](https://github.com/zephyrproject-rtos/gsoc-2022-arduino-core)

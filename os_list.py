#!/bin/python3

import argparse
import json
from pathlib import Path

DIST = Path("dist/")

DESCRIPTION = "MicroBlocks is a blocks programming language for physical computing inspired by Scratch."
ICON = "https://raw.githubusercontent.com/beagleboard/bb-imager-rs/refs/heads/main/assets/os/microblocks.svg"


def get_file_sha256(file_path: Path) -> str:
    # Open the file in binary read mode ('rb')
    with open(file_path, "rb") as f:
        # Generate the file digest using SHA-256
        digest = hashlib.file_digest(f, "sha256")
    return digest.hexdigest()


def get_xz_extract_size(file_path: Path) -> int:
    out = subprocess.run(
        ["xz", "--robot", "--list", file_path],
        capture_output=True,
        text=True,
        check=True,
    ).stdout
    return int(out.splitlines()[-1].split("\t")[4])


def os_list_item(
    vm: str,
    fpath: Path,
    release_date: str,
):
    dev = fpath.name.split(".")[0]
    return {
        "name": f"MicroBlocks VM{vm}",
        "description": DESCRIPTION,
        "icon": ICON,
        "url": f"https://github.com/beagleboard/microblocks-zephyr/releases/download/VM{vm}/{fpath.name}",
        "image_download_size": fpath.stat().st_size,
        "image_download_sha256": get_file_sha256(fpath),
        "release_date": release_date,
        "extract_size": get_xz_extract_size(fpath),
        "devices": [dev],
    }


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("vm", help="Version of MicroBlocks VM", type=int)
    args = parser.parse_args()

    release_date = datetime.datetime.now().strftime("%Y-%m-%d")

    os_list = list(
        map(lambda x: os_list_item(args.vm, x, release_date), DIST.iterdir())
    )

    with open(f"{DIST}/os_list.json", "w") as fp:
        json.dump({"os_list": os_list}, fp)

# Hey, me from the future. This is how I flashed the keyboards step by step

1. Install the QMK (Source https://docs.qmk.fm/newbs_getting_started)

```console
curl -fsSL https://install.qmk.fm | sh
```

2. Run the setup script (Source https://qmk.fm/guide)

```console
qmk setup d3n13/qmk_firmware
```

3. Make changes in `keyboards/`

4. Plug the target half of the board 

5. Run the `qmk flash -c -kb {keyboard} -km {keymap}` for the keyboard and keymap of choice to flash the firmware onto the unit

6. When you see `Waiting for drive to deploy...`, hit the reset button on the borard (twice)

## Charybdis Nano

-   Store: https://bastardkb.com/product/charybdis-nano-kit/
-   Build repo: https://github.com/Bastardkb/Charybdis
-   BastardKB QMK fork: https://github.com/Bastardkb/bastardkb-qmk (Didn't use this one)

> QMK pulls [master branch from `qmk_firmware`](https://github.com/qmk/qmk_firmware) during install/setup. I used that.

> On top of that, I changed some files to achieve desired layout/behaviour

> Upstream removed the `v2/splinky_3` target (qmk/qmk_firmware#25488). The Splinky is now built as the `elitec` board plus the `rp2040_ce` converter. My former `splinky_3` tweaks (MASTER_RIGHT, mouse keys, combos, caps word, RGB off) live in `keymaps/default/config.h` and `rules.mk`. Don't use the old `v2/splinky_3` name: it's now an alias for plain `elitec` and builds AVR firmware that won't flash.

> Then I run `qmk flash -c -kb bastardkb/charybdis/3x5/elitec -km default -e CONVERT_TO=rp2040_ce` on both sides, while making sure I only connect one half at a time via USB-C cable, and without connecting the other half via TRRS until I'm certaing that both sides run the same version of QMK with correct firmware

## Dasbob

-   Store: https://shop.beekeeb.com/product/dasbob-split-keyboard-pcb-kit
-   Build repo: https://github.com/GroooveBob/DASBOB
-   BastardKB QMK fork: https://github.com/GroooveBob/DASBOB-qmk (Did I use this one? Not sure)

> QMK pulls [master branch from `qmk_firmware`](https://github.com/qmk/qmk_firmware) during install/setup. I used that as a base.

> On top of that, I've moved the `dasbob` folder into the keyboards

> Then I run `qmk flash -c -kb dasbob -km default -bl uf2-split-left` on left side and `qmk flash -c -kb dasbob -km default -bl uf2-split-right` on the right one, while making sure I only connect one half at a time via USB-C cable, and without connecting the other half via TRRS until I'm certaing that both sides run the same version of QMK with correct firmware

> Important note: **Never plug in USB-C cables into both halfes while they are connected via TRRS cable** - This will fry both controllers. I did that once and they refused to work as 1 board ever since (only as individual pieces). Only swapping both controllers helped.

## Useful links

-   QMK keycodes https://docs.qmk.fm/keycodes

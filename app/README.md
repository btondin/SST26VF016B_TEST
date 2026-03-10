# SST26VF016B SPI Flash Test

Test application for the **Microchip SST26VF016B** 16 Mbit (2 MB) SPI NOR flash memory on **Zephyr RTOS**, using the `jedec,spi-nor` driver and the Zephyr Flash API (`flash_erase`, `flash_write`, `flash_read`).

## Test Steps

1. Erase a 4 KB sector at offset `0x0000`
2. Verify erase (all bytes `0xFF`)
3. Write 256 bytes with sequential pattern (`0x00..0xFF`)
4. Read back and verify data integrity

## Flash Memory

| Property | Value |
|---|---|
| Part | SST26VF016B |
| Capacity | 16 Mbit (2 MB) |
| Interface | SPI (supports SPI and SQI/Quad-SPI) |
| Manufacturer | Microchip (SST) |
| JEDEC ID | `BF 26 41` |
| SFDP | v1.6 (JESD216F), 3 parameter headers |

## Hardware

- **MCU**: nRF52832 (custom board `bruno_nrf52832`)
- **Flash**: SST26VF016B on SPI1

### Pinout (SPI1)

| Signal | Pin | Description |
|---|---|---|
| SCK | P0.11 | SPI Clock |
| MOSI | P0.12 | Master Out |
| MISO | P0.13 | Master In |
| CS | P0.19 | Chip Select |

## Configuration

Key Kconfig options (`prj.conf`):

- `CONFIG_SPI_NOR=y` — SPI NOR flash driver
- `CONFIG_SPI_NOR_SFDP_RUNTIME=y` — read SFDP parameters from chip at boot
- `CONFIG_FLASH_MAP=y` / `CONFIG_STREAM_FLASH=y` — flash map support

Key devicetree properties (overlay):

- `requires-ulbpr` — mandatory for SST26VF series (unlocks block protection)
- `spi-max-frequency = <1000000>` — 1 MHz for protoboard
- `sfdp-bfp` — BFP bytes included commented out for future use with `CONFIG_SPI_NOR_SFDP_DEVICETREE`

## Building and Flashing

```bash
west build -b bruno_nrf52832/nrf52832
west flash
```

## Expected Output

```
sst26wf016ba@0: SFDP v 1.6 AP ff with 3 PH
sst26wf016ba@0: 2 MiBy flash
=== SST26VF016B Flash Test ===
Flash device sst26wf016ba@0 is ready
Erasing 4096 bytes at offset 0x0000 ...
Erase OK
Erase verify OK (all 0xFF)
Writing 256 bytes at offset 0x0000 ...
Write OK
Read-back verify OK - all 256 bytes match!
=== Test complete ===
```

## License

Apache-2.0

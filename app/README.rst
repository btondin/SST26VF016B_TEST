SST26VF016B SPI Flash Test
==========================

Overview
********

Test application for the **Microchip SST26VF016B** 16 Mbit (2 MB) SPI NOR
flash memory on **Zephyr RTOS**, using the ``jedec,spi-nor`` driver and
the Zephyr Flash API.

Flash Memory
************

* **Part**: SST26VF016B
* **Capacity**: 16 Mbit (2 MB)
* **Interface**: SPI (supports SPI and SQI/Quad-SPI)
* **Manufacturer**: Microchip (SST)

Hardware
********

* **MCU**: nRF52832 (custom board ``bruno_nrf52832``)
* **Flash**: SST26VF016B on SPI bus

Building and Flashing
*********************

::

    west build -b bruno_nrf52832/nrf52832
    west flash

License
*******

Apache-2.0

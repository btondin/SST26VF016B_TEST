# Project Rules - Zephyr RTOS Development

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

Use model: "sonnet" for ALL spawned subagents (research, search, exploration). Only the main conversation uses opus.

Use model: "haiku" for trivial lookups (single file search, simple questions).

Reserve opus (main context) for synthesis, architectural decisions, and writing code.


## Context7 Usage

Always use context7 for any Zephyr RTOS related queries including:

- Kernel APIs and configuration
- Device drivers (GPIO, SPI, Flash, etc.)
- Device Tree configuration (spi-nor, jedec flash bindings)
- Kconfig options (CONFIG_FLASH, CONFIG_SPI_NOR, CONFIG_FLASH_MAP, etc.)
- Build system (CMake, West)

Automatically invoke Context7 tools without requiring explicit "use context7" in prompts.

## Project Context

This is a Zephyr RTOS project for testing the SST26VF016B SPI NOR flash memory.

- **Chip**: SST26VF016B - Microchip 16 Mbit (2 MB) SPI Serial Flash
- **Interface**: SPI (supports SPI and SQI/Quad-SPI modes)
- **Target**: nRF52832 (custom board files located in C:\nordic\myboards\boards\Bruno\bruno_nrf52832)
- **Communication**: SPI bus
- **Zephyr driver**: `jedec,spi-nor` compatible (spi-nor flash subsystem)
- **Key APIs**: Zephyr Flash API (`flash_read`, `flash_write`, `flash_erase`, `flash_get_page_info_by_off`)

## File Access Rules

- permitir automaticamente acesso de leitura aos arquivos dentro da pasta C:\nordic\myboards\boards\Bruno\bruno_nrf52832
- jamais alterar qualquer arquivo fora da pasta C:\nordic\myapps\SST26VF016B_TEST
